from matplotlib.pyplot import get
from pandas_datareader.data import get_quote_yahoo

jpyx = get_quote_yahoo('JPY=X')
eurx = get_quote_yahoo('EUR=X')
# gbpx = get_quote_yahoo('GPB=X')
audx = get_quote_yahoo('AUD=X')

# print(jpyx.columns.values) # 得られる列情報一覧

ary_USD = jpyx["price"].values
ary_EUR = jpyx["price"].values / eurx["price"].values
# ary_GBP = jpyx["price"].values / gbpx["price"].values
ary_AUD = jpyx["price"].values / audx["price"].values

price_USD = ary_USD[0]
price_EUR = ary_EUR[0]
# price_GBP = ary_GBP[0]
price_AUD = ary_AUD[0]

print(
    # f'USD = {price_USD}\tEUR = {price_EUR}\GBP = {price_GBP}\tAUD = {price_AUD}\n')
    f'USD = {price_USD}\tEUR = {price_EUR}\tAUD = {price_AUD}\n')

# ary_result = jpyx["price"].values
# price = ary_result[0]

# print(price)
