import cv2
import time
import numpy as np
import pyautogui

# lab_windows
# movie = cv2.VideoCapture('C:/Users/Kitadai/Videos/test.mp4')

# droidcam
movie = cv2.VideoCapture('http://192.168.0.3:4747/video')

# iriunwebcam for ubuntu
# movie = cv2.VideoCapture(1)

# iriunwebcam for windows
# movie = cv2.VideoCapture(0)

before = None  # 前回の画像を保存する変数
fps = int(movie.get(cv2.CAP_PROP_FPS))  # 動画のFPSを取得

# ウィンドウでの再生速度を元動画と合わせる
time.sleep(1/fps)

# 画像を取得
ret, frame = movie.read()

# 画像の取得が安定するように2秒間停止
# time.sleep(2)

while True:
    # 画像を取得
    ret, frame = movie.read()
    # 再生が終了したらループを抜ける
    if ret == False:
        break
    # 白黒画像に変換
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    if before is None:
        before = gray.astype("float")
        continue

    # 現在のフレームと移動平均との差を計算
    cv2.accumulateWeighted(gray, before, 0.95)
    frameDelta = cv2.absdiff(gray, cv2.convertScaleAbs(before))

    # frameDeltaの画像を２値化
    thresh = cv2.threshold(frameDelta, 3, 255, cv2.THRESH_BINARY)[1]

    # ウィンドウで表示する場合

    # 輪郭のデータを得る
    contours = cv2.findContours(
        thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]

    # ウィンドウで表示
    # cv2.imshow('target_frame', gray)
    # cv2.imshow('target_frame', frameDelta)
    # cv2.imshow('target_frame', thresh)
    # cv2.imshow('target_frame', contours)

    pixel_number = np.size(contours)  # 全ピクセル数をpixel_numberに代入
    pixel_sum = np.sum(contours)  # 全ピクセルの輝度の合計をpixel_sumに代入
    white_pixel_number = pixel_sum/255  # 白いピクセルの数を計算しwhite_pixel_numberに代入
    print(white_pixel_number)  # 白いピクセルの数を表示

    # 白いピクセルの数が一定値を超えたら画面を変更 or Enterキーが押されたらループを抜ける
    if white_pixel_number > 9000:
        pyautogui.hotkey('winleft', 'winright', 'd')
        break

    elif cv2.waitKey(1) == 13:
        break

cv2.destroyAllWindows()  # ウィンドウを破棄
