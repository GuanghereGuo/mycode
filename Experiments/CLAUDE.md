# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

这是大学「信号与系统」和「模拟电子电路」课程的实验代码与报告仓库。代码主要使用 MATLAB (.m) 和 Python（Jupyter Notebook、独立脚本），报告使用 LaTeX (.tex) 编写。Python 包管理使用 `uv`。

## 常用命令

```bash
# Python 环境（需要 Python >= 3.13）
uv sync                          # 安装依赖
uv run jupyter notebook          # 启动 Jupyter Notebook

# LaTeX 编译
latexmk -pdf -xelatex report.tex # 编译单个实验报告
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

MATLAB/                          # MATLAB 辅助函数（阶跃响应等）
reference/                       # 参考材料（MinerU 提取的 PDF）
compress.py                      # 压缩当前目录下所有 JPG 图片
```

## 数电实验约定

- 每个实验独立目录，命名 `N. topic_name/`
- 每个目录含 `report.tex` + 源码（`.v` / `.bdf`）+ `figures/` 截图和照片
- 仅提交源码和截图，不提交 Quartus 工程缓存（`db/`、`incremental_db/` 等）
- Quartus 目标器件：Cyclone V 5CEBA4F23C7（DE0 开发板）
- LaTeX 报告使用 `ctexrep` 文档类，xelatex 编译
- LaTeX 编译：`latexmk -pdf -xelatex report.tex`

## 关键依赖

Python: `numpy`, `scipy`, `matplotlib`, `jupyterthemes`, `notebook`
MATLAB 代码需要 Signal Processing Toolbox（`audioread`, `audiowrite`, `sound`, `stepfun` 等函数）

## 注意事项

- Python 代码在 Jupyter Notebook 中使用 `SimHei`（黑体）中文字体绘图，需要系统安装该字体
- LaTeX 报告使用 `ctexrep` 文档类，需 xelatex 编译以支持中文
- MATLAB `.m` 文件中有大量注释掉的代码块，这些是不同信号波形的绘制片段，用于教学演示
