# OpenCV のインポート
import cv2
import face_recognition
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ('172.20.10.6', 2390)

# Sending data for rotation
def sendData(msg):
    sock.sendto(msg.encode('utf8'), addr)


# VideoCaptureのインスタンスを作成する。
# 引数でカメラを選べれる。
cap = cv2.VideoCapture(1)

while True:
    # VideoCaptureから1フレーム読み込む
    ret, frame = cap.read()

    # 1/2サイズに縮小
    frame = cv2.resize(frame, (int(frame.shape[1]/2), int(frame.shape[0]/2)))
    # 加工なし画像を表示する
    # cv2.imshow('Raw Frame', frame)

    # Getting face location
    edframe = frame
    height, width, channels = edframe.shape
    offset = width/15
    face_locations = face_recognition.face_locations(frame)
    # face_locations = face_recognition.face_locations(frame, model="cnn")  # too heavy
    print(face_locations)

    rect_color = (255, 0, 0)
    if len(face_locations) > 0:
        for top, left, bottom, right in face_locations:
            cv2.rectangle(edframe, (left, top), (right, bottom), rect_color, thickness=3)

            # Sending data for rotation
            face_x = (left+right)/2
            msg = 'stay'
            if face_x < width/2-offset:
                msg = 'left'
            if face_x > width/2+offset:
                msg = 'right'
            sendData(msg)

    # 加工済の画像を表示する
    cv2.imshow('Edited Frame', edframe)

    # キー入力を1ms待って、k が27（ESC）だったらBreakする
    k = cv2.waitKey(1)
    if k == 27:
        break

# キャプチャをリリースして、ウィンドウをすべて閉じる
cap.release()
cv2.destroyAllWindows()
