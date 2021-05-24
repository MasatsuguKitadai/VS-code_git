import time
import datetime
import cv2

# 画像保存ディレクトリ
save_dir = './image/'
file_suffix = 'detect.jpg'

# カメラ映像を取得
cam = cv2.VideoCapture('http://192.168.0.3:4747/video')
# Video Graphics Array（略称:VGA）を設定
cam.set(3, 640)  # set video 横
cam.set(4, 480)  # set video 高さ

# 2値化したときのピクセル値
DELTA_MAX = 255
# ドットの変化を検知する閾値
DOT = 8
# 比較用のデータを格納
avg = None

while True:
    # 1フレームずつ取得する。
    ret, frame = cam.read()
    if not ret:
        break
    # 画像ファイル名用の時間取得
    date = datetime.datetime.now()
    file_name = str(date) + file_suffix

    # グレースケールに変換
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 比較用のフレームを取得するavgがNoneの場合進むつまり、値があればコピーしていく
    if avg is None:
        avg = gray.copy().astype("float")
        continue

    # 現在のフレームと移動平均との差を計算
    cv2.accumulateWeighted(gray, avg, 0.6)
    frameDelta = cv2.absdiff(gray, cv2.convertScaleAbs(avg))

    # デルタ画像を閾値処理を行う 閾値処理された後の二値画像が帰ってくる
    thresh = cv2.threshold(frameDelta, DOT, DELTA_MAX, cv2.THRESH_BINARY)[1]

    # 画像の閾値に輪郭線を入れる　戻り値は(画像、輪郭、階層)
    img, contours, hierarchy = cv2.findContours(
        thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 輪郭の面積を求めてデータサイズを超えるものを見つけた場合検知とする
    max_area = 0
    for cnt in contours:
        area = cv2.contourArea(cnt)  # この時の輪郭の値を計算して面積を求める
        if max_area < area:
            max_area = area
        if max_area > 1500:  # 面積は目的に適した値に調節
            frame = cv2.drawContours(frame, contours, -1, (0, 255, 0), 3)
            cv2.imwrite(save_dir + file_name, frame)
            print("動体検知しました")
        break
    else:
        pass

    frame = cv2.drawContours(frame, contours, -1, (0, 255, 0), 3)
    # 結果を出力
    cv2.imshow("Frame", frame)
    key = cv2.waitKey(30)
    if key == 27:
        break

cam.release()
cv2.destroyAllWindows()
