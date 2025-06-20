import pandas as pd

# 读取Excel文件
df_diss = pd.read_excel('data.xlsx', sheet_name='Sheet1', index_col=0)
df_neg = pd.read_excel('data.xlsx', sheet_name='Sheet2', index_col=0)

# 将数据保存到TXT文件
df_diss.to_csv('diss.txt', sep='\t', header=False, index=False)
df_neg.to_csv('neg.txt', sep='\t', header=False, index=False)

print("数据已保存到 diss.txt 和 neg.txt")