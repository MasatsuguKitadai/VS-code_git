import cv2

# cap = cv2.VideoCapture('http://192.168.0.3:4747/video')
# webcam for ubuntu
cap = cv2.VideoCapture(0)

while True:

    ret, frame = cap.read()
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == 13:
        break

cap.release()
cv2.destroyAllWindows()
