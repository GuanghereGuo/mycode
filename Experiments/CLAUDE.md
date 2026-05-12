# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

这是大学「信号与系统」、「模拟电子电路」、「数字电子技术」和「电路基础」课程的实验代码与报告仓库。代码主要使用 MATLAB (.m) 和 Python（Jupyter Notebook、独立脚本），报告使用 LaTeX (.tex) 编写。Python 包管理使用 `uv`。

## 常用命令

```bash
# Python 环境（需要 Python >= 3.13）
uv sync                          # 安装依赖
uv run jupyter notebook          # 启动 Jupyter Notebook

# LaTeX 编译（产物集中到 build/，不污染源目录）
cd <tex_dir> && latexmk -xelatex -outdir=build <name>.tex
```

## 目录结构

```
signal/                          # 信号与系统实验（共 7 个实验 + 大作业）
  ├── 1. common signals/         # 常见信号（指数、sinc、高斯等）+ 数据拟合
  ├── 2. impluse_step/           # 阶跃响应与冲击响应
  ├── 3. convolution/            # 卷积
  ├── 4. frequency/              # 频率特性（低通无源/有源滤波器）
  ├── 5. sample/                 # 采样
  ├── 6. filter/                 # 滤波器设计
  ├── 7. sound/                  # 音频处理（倒放等）
  ├── major assignment/          # 课程大作业
  │   ├── task1/                 # 含噪信号滤波
  │   ├── task3/                 # WSOLA 与 Phase Vocoder 变调/变速
  │   └── task4/                 # 音频倒放与拼接
  └── main.tex                   # 汇总报告主文件

AnalogElectricity/               # 模电实验
  ├── report.tex                 # 实验报告
  ├── figures/                   # 实验图片（1_Co_shot ~ 6_Filter）
  └── auxiliary files/           # 辅助数据与 Python 绘图脚本

DigitalElectronics/              # 数电实验（共 8 个实验）
  ├── 参考资料/                   # 教师提供的实验要求 PDF 和模板
  ├── 1. full_adder/             # 实验一：TTL集成门电路逻辑变换（一位全加器）
  │   ├── report.tex             # 实验报告
  │   ├── figures/               # 原理图截图、波形截图、实验照片
  │   └── *.v / *.bdf            # Verilog 源码或 Quartus 原理图文件
  └── N. topic_name/             # 后续实验类推

CircuitTheory/                   # 电路基础实验
  ├── reference.docx             # 学校实验报告模板（Word）
  ├── reference.pdf              # 学校实验报告模板（PDF）
  ├── requirements/              # 格式要求、提取的仿真图片
  │   ├── requirements.md        # 教师要求汇总
  │   └── extracted_images/      # 从 reference.docx 提取的图片
  ├── preview.tex                # 预习报告 LaTeX 模板
  ├── template.tex               # 正式实验报告 LaTeX 模板
  └── N. topic_name/             # 各实验目录
      ├── preview.tex            # 预习报告（实验前完成）
      ├── report.tex             # 实验报告（实验后完成）
      └── figures/               # 截图和照片

MATLAB/                          # MATLAB 辅助函数（阶跃响应等）
reference/                       # 参考材料（MinerU 提取的 PDF）
compress.py                      # 压缩当前目录下所有 JPG 图片
```

## 电路基础实验约定

- 每个实验独立目录，命名 `N. topic_name/`
- 每个目录通常含 `preview.tex`（预习报告）+ `report.tex`（正式实验报告）+ `figures/` 截图和照片
- 模板使用 `ctexart` 文档类，xelatex 编译
- LaTeX 编译：`cd CircuitTheory/N.\ topic_name && latexmk -xelatex -outdir=build <name>.tex`
- **预习报告和正式实验报告是两个完全不同的文件**，格式和内容不同
- `CircuitTheory/preview.tex` 是预习报告模板；`CircuitTheory/template.tex` 是正式实验报告模板，二者不可混用
- 预习报告使用简洁文字封面；正式实验报告使用 `template.tex` 的校徽正式封面（校徽/课程名/“实验报告”/实验标题/课程、姓名学号、组号、时间信息表）
- 预习报告（`preview.tex`）：(10)实验目的 → (80)实验原理（理论分析、公式推导、Multisim 仿真图和仿真结果） → (10)实验器件
- 正式实验报告（`report.tex`）：(10)实验目的 → (20)实验原理 → (10)实验器件 → (10)实验步骤 → (10)实验数据 → (20)数据分析
- 正式报告正文按教师评分项组织：`1、实验目的`、`2、实验原理`、`3、实验器件`、`4、实验步骤`、`5、实验数据`、`6、数据分析`
- **不要写目录、不要写摘要**；参考文献放报告最后（不单独占一页）；页码使用模板默认设置
- 图片优先放入对应实验目录的 `figures/`；Multisim 仿真图应使用本实验对应的仿真图，若实验目录缺少本实验仿真图，应优先从 `CircuitTheory/requirements/extracted_images/word/media/` 中识别并选取对应实验电路图
- 教师资料/PPT/PDF 提取图可用于 Multisim 仿真图或原理参考，但不能替代实物照片、示波器截图、原始数据记录页、教师签名页
- 用户已明确命名的实验图片默认按名称判断用途；未命名微信图默认先按 PPT/参考材料处理，不插入正式报告，除非用户另行说明
- 数据不能只保留在照片中，正式报告必须整理为表格；看不清或无法可靠推断的数据用 `xx`，不得编造
- 正式报告的数据分析必须围绕本实验目的和原理定制：比较理论/仿真/实测数据，计算必要误差或对比量，解释偏差来源并给出结论；不要套用其他实验的专属分析方式
- 若记录参考方向混乱，应先根据实际电路拓扑统一参考方向，再整理正负号和数据表；无法判断时询问用户
- 材料齐全时 Claude 默认自主完成电基报告并编译；只有关键数据缺失、数据看不清、参考方向无法判断或图片性质冲突时再询问
- 文件命名格式：`姓名_学号_电路基础实验报告_N`
- 教师要求详见 `CircuitTheory/requirements/requirements.md`

## 数电实验约定

- 每个实验独立目录，命名 `N. topic_name/`
- 每个目录含 `report.tex` + 源码（`.v` / `.bdf`）+ `figures/` 截图和照片
- 仅提交源码和截图，不提交 Quartus 工程缓存（`db/`、`incremental_db/` 等）
- Quartus 目标器件：Cyclone V 5CEBA4F23C7（DE0 开发板）
- LaTeX 报告使用 `DigitalElectronics/template.tex`（与电路基础正式报告同款校徽封面，已按数电课程标题和组员字段调整），`ctexart` 文档类，xelatex 编译
- LaTeX 编译：`cd DigitalElectronics/N.\ topic_name && latexmk -xelatex -outdir=build report.tex`
- 数电报告正文结构：`一、实验目的`、`二、实验要求`、`三、实验设备`、`四、实验原理`、`五、实验内容`、`六、实验过程中的问题`、`七、心得体会`
- 若待完成的具体实验目录内存在说明文件，则忽略 `DigitalElectronics/参考资料/` 中的 PDF 说明，严格按当前实验目录说明文件执行
- 若实验目录无单独说明文件，撰写数电报告前必须先查看 `DigitalElectronics/参考资料/` 中对应实验要求 PDF
- `DigitalElectronics/别人的报告/` 中有已完成报告，必要时可参考其内容组织和表述
- 用户提前放入实验 `figures/` 的图片必须按内容和文件名判断用途，并插入报告合适位置，不得遗漏

## 关键依赖

Python: `numpy`, `scipy`, `matplotlib`, `jupyterthemes`, `notebook`
MATLAB 代码需要 Signal Processing Toolbox（`audioread`, `audiowrite`, `sound`, `stepfun` 等函数）

## 注意事项

- Python 代码在 Jupyter Notebook 中使用 `SimHei`（黑体）中文字体绘图，需要系统安装该字体
- LaTeX 报告按各课程现有模板选择文档类；电路基础和数电当前模板使用 `ctexart`，需 xelatex 编译以支持中文
- MATLAB `.m` 文件中有大量注释掉的代码块，这些是不同信号波形的绘制片段，用于教学演示
