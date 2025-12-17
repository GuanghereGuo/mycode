import os
import pyworld as pw
import soundfile as sf
import numpy as np
import scipy.interpolate

# --- 保持之前的 resize_spectral_envelope 函数不变 ---
def resize_spectral_envelope(sp, ratio):
    N, D = sp.shape
    new_sp = np.zeros_like(sp)
    freq_axis = np.arange(D)
    for i in range(N):
        f = scipy.interpolate.interp1d(freq_axis, sp[i, :], kind='linear', fill_value="extrapolate")
        new_sp[i, :] = f(freq_axis / ratio)
    return new_sp

def convert_voice_high_quality(input_path, output_path):
    # 1. 读取音频
    x, fs = sf.read(input_path)
    if x.ndim > 1: x = x.mean(axis=1)
    x = x.astype(np.float64)

    print("1. 正在使用 Harvest 算法提取基频 (速度较慢，请耐心)...")
    
    # === 改动点 1: 使用 Harvest 替代 Dio ===
    # Harvest 能极大减少呼吸声被错误识别为电流声的概率
    f0, t = pw.harvest(x, fs)
    
    print("2. 提取频谱包络 (CheapTrick)...")
    # 使用 CheapTrick 算法提取频谱 (WORLD 标准做法)
    sp = pw.cheaptrick(x, f0, t, fs)
    
    print("3. 提取非周期性指数 (D4C)...")
    # 使用 D4C 算法提取噪音成分 (呼吸声、嘶嘶声)
    ap = pw.d4c(x, f0, t, fs)

    # === 改动点 2: 参数微调 ===
    # 为了减少机械感，不要拉得太狠
    pitch_ratio = 1.5      # 稍微降低一点 (之前是 1.6)
    formant_ratio = 1.12   # 稍微降低一点 (之前是 1.15)

    # 4. 修改参数
    new_f0 = f0 * pitch_ratio
    
    # 这一步是为了防止把本来就是 0 (无声) 的地方变出声音来
    # 只有原来不是 0 的地方才乘以系数
    new_f0[new_f0 < 50] = 0 

    new_sp = resize_spectral_envelope(sp, formant_ratio)

    print("4. 合成音频...")
    y = pw.synthesize(new_f0, new_sp, ap, fs, pw.default_frame_period)

    # 归一化
    if np.max(np.abs(y)) > 1.0:
        y = y / np.max(np.abs(y)) * 0.9

    sf.write(output_path, y, fs)
    print(f"完成! 已保存: {output_path}")

if __name__ == "__main__":
    current_dir = os.path.dirname(os.path.abspath(__file__))
    input_path = os.path.join(current_dir, "origin.wav")
    output_path = os.path.join(current_dir, "output_better.wav")

    try:
        convert_voice_high_quality(input_path, output_path)
    except Exception as e:
        print(f"错误: {e}")