from pandas_datareader.data import get_data_yahoo
from sklearn.compose import ColumnTransformer

jpyx = get_data_yahoo('JPY=X', start='2021-4-1', end='2022-4-1')
eurx = get_data_yahoo('EUR=X', start='2021-4-1', end='2022-4-1')
audx = get_data_yahoo('AUD=X', start='2021-4-1', end='2022-4-1')

# print(jpyx.columns.values.tolist()

# EUR x JPY の計算
eurx['High_jpy'] = jpyx['High'] / eurx['High']
eurx['Low_jpy'] = jpyx['Low'] / eurx['Low']
eurx['Open_jpy'] = jpyx['Open'] / eurx['Open']
eurx['Close_jpy'] = jpyx['Close'] / eurx['Close']

# AUD x JPY の計算
audx['High_jpy'] = jpyx['High'] / audx['High']
audx['Low_jpy'] = jpyx['Low'] / audx['Low']
audx['Open_jpy'] = jpyx['Open'] / audx['Open']
audx['Close_jpy'] = jpyx['Close'] / audx['Close']

# 結果の出力
print(jpyx[['High', 'Low', 'Open', 'Close']])
print(eurx[['High_jpy', 'Low_jpy', 'Open_jpy', 'Close_jpy']])
print(audx[['High_jpy', 'Low_jpy', 'Open_jpy', 'Close_jpy']])

# csv 形式での保存
jpyx.to_csv('data/jpy.csv',
            columns=['High', 'Low', 'Open', 'Close'])
eurx.to_csv('data/eur.csv',
            columns=['High_jpy', 'Low_jpy', 'Open_jpy', 'Close_jpy'])
audx.to_csv('data/aud.csv',
            columns=['High_jpy', 'Low_jpy', 'Open_jpy', 'Close_jpy'])
