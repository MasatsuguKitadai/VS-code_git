import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

usd = pd.read_csv("data/jpy.csv")

# print(usd)

# 移動平均の計算
usd['ma(3)'] = usd['Close'].rolling(3).mean()
usd['ma(5)'] = usd['Close'].rolling(5).mean()
usd['ma(7)'] = usd['Close'].rolling(7).mean()

print(usd)

# グラフの作成

usd.plot()
plt.savefig('test_usd.svg')
plt.close('all')
