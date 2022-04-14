import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score

df = pd.read_csv('iris.csv')

# print(df)

# 特徴量
X = df[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]

# 正解
y = df['Species']

# test_size は 評価用のデータを20%と定めている
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=77
)

# 数値予測用の回帰モデルとクラスを予測する分類用のモデル

clf = RandomForestClassifier(random_state=77)  # モデルの変更は関数を変えるだけでできる

clf.fit(X_train, y_train)  # 学習フェーズ

pred = clf.predict(X_test)  # 予測フェーズ

# print(pred)

accuracy = accuracy_score(y_test, pred)  # 評価フェーズ

print(accuracy)

# 文字列はエラーに！！
# → 文字列を数値に置き換える必要がある
# (1) label encording
# (2) one-hot encordeing

# オススメのライブラリ 'Category Encorders'

# 'リーク'について
# → 誤ったデータを用いて学習が行われ，精度が低下する
