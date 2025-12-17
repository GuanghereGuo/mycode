import parselmouth
from parselmouth.praat import call
import os
import numpy as np

def change_gender_robust(input_path, output_path):
    # 1. 读取音频
    if not os.path.exists(input_path):
        print(f"错误: 找不到文件 {input_path}")
        return
        
    sound = parselmouth.Sound(input_path)
    
    # === 修复步骤 1: 强制转单声道 ===
    if sound.n_channels > 1:
        print("检测到立体声，转换为单声道...")
        sound = call(sound, "Convert to mono")

    # === 修复步骤 2: 强制最大化音量 (Scale Intensity) ===
    # 这步非常关键！很多时候没声音是因为输入太轻了
    print("正在标准化音量...")
    call(sound, "Scale intensity", 70) # 将音量统一拉到 70dB

    # === 修复步骤 3: 调整检测范围 ===
    # 将最小频率从 75Hz 降低到 50Hz，防止低沉男声检测不到
    # 将最大频率从 600Hz 降低到 500Hz，减少高频噪音干扰
    min_pitch = 50.0
    max_pitch = 500.0
    
    # 变声参数
    formant_shift = 1.2    # 1.2 = 女声 (声道变短)
    new_pitch_median = 230.0 # 目标基频中位数
    pitch_range = 1.0
    duration_factor = 1.0

    print(f"正在处理: {input_path} (F0范围: {min_pitch}-{max_pitch}Hz)...")
    
    try:
        # 调用核心函数
        new_sound = call(sound, "Change gender", 
                         min_pitch, max_pitch, 
                         formant_shift, new_pitch_median, 
                         pitch_range, duration_factor)
        
        # === 修复步骤 4: 输出归一化 ===
        # 再次确保输出音量正常，防止处理后声音变小
        call(new_sound, "Scale intensity", 70)
        call(new_sound, "Scale peak", 0.99) # 防止爆音

        new_sound.save(output_path, "WAV")
        print(f"✅ 成功！已保存至: {output_path}")
        print("请播放试听。如果还是没声音，说明原录音的信噪比太差（噪音比人声还大）。")
        
    except Exception as e:
        print(f"❌ 处理失败: {e}")

if __name__ == "__main__":
    current_dir = os.path.dirname(os.path.abspath(__file__))
    input_file = os.path.join(current_dir, "origin.wav")
    output_file = os.path.join(current_dir, "output_female_fixed.wav")
    
    change_gender_robust(input_file, output_file)