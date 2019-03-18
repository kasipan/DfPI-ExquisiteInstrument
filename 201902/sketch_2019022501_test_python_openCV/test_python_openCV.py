# OpenCV のインポート
import cv2
import face_recognition

# VideoCaptureのインスタンスを作成する。
# 引数でカメラを選べれる。
cap = cv2.VideoCapture(1)

while True:
    # VideoCaptureから1フレーム読み込む
    ret, frame = cap.read()

    # 1/2サイズに縮小
    frame = cv2.resize(frame, (int(frame.shape[1]/2), int(frame.shape[0]/2)))
    # 加工なし画像を表示する
    cv2.imshow('Raw Frame', frame)

    # 何か処理（ここでは文字列「hogehoge」を表示する）
    edframe = frame
    face_locations = face_recognition.face_locations(frame)
    # face_locations = face_recognition.face_locations(frame, model="cnn")  # too heavy
    print(face_locations)

    rect_color = (255, 0, 0)
    if len(face_locations) > 0:
        for top, left, bottom, right in face_locations:
            cv2.rectangle(edframe, (left, top), (right, bottom), rect_color, thickness=3)

    # 加工済の画像を表示する
    cv2.imshow('Edited Frame', edframe)

    # キー入力を1ms待って、k が27（ESC）だったらBreakする
    k = cv2.waitKey(1)
    if k == 27:
        break

# キャプチャをリリースして、ウィンドウをすべて閉じる
cap.release()
cv2.destroyAllWindows()
