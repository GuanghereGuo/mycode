#!/usr/bin/env python3
"""把 7 个数电实验报告整合成一份综合报告。

读取各实验目录的 report.tex，抽取正文并改写，拼装出 final/综合报告.tex。
7 个原始 report.tex 保持不动，仅作只读输入。

改写规则（每个实验块）：
1. 抽取正文：从第一个 \\section{ 到 \\end{document} 之前。
2. 限定图片目录：块首插入 \\graphicspath，只搜本实验 figures，避免跨实验同名图冲突。
3. 标签加实验前缀：\\label/\\ref/\\eqref/\\autoref/\\pageref/\\subref 的键加 eN: 前缀，
   避免跨实验同名标签互相串号。
4. 加章标题：用封面里的实验标题（去掉「实验N：」前缀）作 \\chapter，
   配合导言区 \\ctexset 自动显示为「实验1 标题」。
"""
import re
from pathlib import Path

# final/ 的上一级即 DigitalElectronics/
ROOT = Path(__file__).resolve().parent.parent

# 按实验顺序排列的目录名
DIRS = [
    "1. full_adder",
    "2. sub",
    "3. segment",
    "4. fpga",
    "5. rom",
    "6. adda",
    "7. adda2",
]

# 抽取封面实验标题：\LARGE\textbf{实验...}
TITLE_RE = re.compile(r"\\LARGE\\textbf\{(实验[^}]*)\}")
# 去掉标题里的「实验N：」前缀，留纯标题（章号由 \ctexset 自动补「实验1」）
PREFIX_RE = re.compile(r"^实验[一二三四五六七八九十]+\s*[：:]\s*")
# 交叉引用命令的键加前缀；较长的命令名排在前，\ref 放最后
REF_RE = re.compile(r"\\(label|eqref|autoref|pageref|subref|ref)\{([^}]*)\}")
# 图片浮动：匹配整个 figure 环境，把位置参数统一改 htbp、缩小单张大图
FIGURE_RE = re.compile(r"\\begin\{figure\}(?:\[[^\]]*\])?(.*?)\\end\{figure\}", re.DOTALL)
WIDTH_RE = re.compile(r"width\s*=\s*([0-9]*\.?[0-9]+)?\\(textwidth|linewidth)")
MAX_FIG_WIDTH = 0.75  # 单张图相对正文宽度上限，超过则压到此值

PREAMBLE = r"""% ============================================================
% 数字电子技术实验 综合报告
% 由 build_combined.py 自动生成，请勿手改；如需修改请改各实验 report.tex 后重跑脚本。
% ============================================================

\documentclass[12pt]{ctexrep}

% --- 宏包（取 7 份报告导言区并集，顺序参照 7. adda2/report.tex）---
\usepackage{graphicx}
\usepackage{amsmath}
\usepackage{xcolor}
\usepackage{listings}
\usepackage{float}
\usepackage{booktabs}
\usepackage{siunitx}
\usepackage{fancyhdr}
\usepackage{caption}
\usepackage{subcaption}
\usepackage[hidelinks]{hyperref}
\usepackage{makecell}
\usepackage{multirow}
\usepackage{enumitem}
\usepackage{minted}

\sisetup{per-mode=symbol}

\usepackage[left=2.5cm, right=2.5cm, top=2.5cm, bottom=2.5cm]{geometry}

\setlength{\jot}{6pt}
\setlength{\headheight}{15pt}
\linespread{1.5}
\setlist{nosep}

% --- 浮动体参数：让整页容纳更多浮动、少用单独浮动页，减少留白 ---
\renewcommand{\topfraction}{0.9}
\renewcommand{\bottomfraction}{0.85}
\renewcommand{\textfraction}{0.08}
\renewcommand{\floatpagefraction}{0.75}
\setcounter{topnumber}{3}
\setcounter{bottomnumber}{2}
\setcounter{totalnumber}{5}

% --- VHDL 代码样式 ---
\setminted[vhdl]{
    fontsize=\small,
    frame=single,
    linenos,
    breaklines,
    tabsize=4,
    numbersep=8pt,
    xleftmargin=2em
}

% --- 章标题显示为「实验1 标题」，章号 arabic，故节/图/表/公式编号为 1.1 等 ---
\ctexset{chapter={name={实验,},number=\arabic{chapter}}}
\setcounter{tocdepth}{1}

% --- 页眉页脚 ---
\pagestyle{fancy}
\fancyhead[C]{数字电子技术实验}
\fancyfoot[C]{\thepage}

\begin{document}

% ==================== 封面 ====================
\thispagestyle{empty}
\graphicspath{{../figures/}}

\begin{figure}[t]
    \centering
    \includegraphics[width=13cm]{logo1.png}
\end{figure}

\vspace*{\fill}
    \begin{center}
        \Huge\textbf{数字电子技术基础}

        \vspace{0.3cm}
        \Huge\textbf{实验报告}
    \end{center}
\vspace*{\fill}

\begin{table}[H]
    \centering
    \large
    \begin{tabular}{ll}
    \toprule
    \textbf{课程:} & 数字电子技术实验 \\
    \textbf{组员1:} & 郭浩然 2024303980 \\
    \textbf{组员2:} & 庞铭洋 2024302539 \\
    \textbf{组号:} & 15 \\
    \textbf{时间:} & \today \\
    \bottomrule
    \end{tabular}
\end{table}

\newpage

% ==================== 目录 ====================
\tableofcontents
\newpage
"""


def extract_title(text: str) -> str:
    m = TITLE_RE.search(text)
    if not m:
        raise RuntimeError("找不到封面实验标题 \\LARGE\\textbf{实验...}")
    return PREFIX_RE.sub("", m.group(1)).strip()


def extract_body(text: str) -> str:
    start = text.find(r"\section{")
    if start < 0:
        raise RuntimeError("找不到正文起始 \\section{")
    end = text.rfind(r"\end{document}")
    if end < 0:
        raise RuntimeError("找不到 \\end{document}")
    return text[start:end].rstrip()


def prefix_labels(body: str, idx: int) -> str:
    return REF_RE.sub(lambda m: f"\\{m.group(1)}{{e{idx}:{m.group(2)}}}", body)


def _shrink_width(m: re.Match) -> str:
    coef = float(m.group(1)) if m.group(1) else 1.0
    coef = min(coef, MAX_FIG_WIDTH)
    return f"width={coef:g}\\{m.group(2)}"


def adjust_figures(body: str) -> str:
    """figure 浮动位置统一为 htbp；单张图宽度封顶到 MAX_FIG_WIDTH。

    含 subfigure 的并排图组只改浮动位置，不动子图宽度，避免破坏布局。
    """
    def repl(m: re.Match) -> str:
        inner = m.group(1)
        if "\\begin{subfigure}" not in inner:
            inner = WIDTH_RE.sub(_shrink_width, inner)
        return r"\begin{figure}[htbp]" + inner + r"\end{figure}"

    return FIGURE_RE.sub(repl, body)


def build() -> str:
    parts = [PREAMBLE]
    for idx, d in enumerate(DIRS, start=1):
        src = (ROOT / d / "report.tex").read_text(encoding="utf-8")
        title = extract_title(src)
        body = prefix_labels(adjust_figures(extract_body(src)), idx)
        block = (
            f"\n% ==================== 实验{idx}：{title} ====================\n"
            f"\\graphicspath{{{{../{d}/figures/}}}}\n"
            f"\\chapter{{{title}}}\n\n"
            f"{body}\n"
        )
        parts.append(block)
    parts.append("\n\\end{document}\n")
    return "".join(parts)


def main() -> None:
    out = ROOT / "final" / "综合报告.tex"
    out.write_text(build(), encoding="utf-8")
    print(f"已生成 {out}")


if __name__ == "__main__":
    main()
