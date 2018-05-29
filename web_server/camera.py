import cv2
from base_camera import BaseCamera


class Camera(BaseCamera):
    video_source = 0
    encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 50]

    @staticmethod
    def set_video_source(source=0):
        Camera.video_source = source

    @staticmethod
    def frames():
        camera = cv2.VideoCapture(Camera.video_source)
        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, img = camera.read()

            img = cv2.resize(img, (320,240))

            # encode as a jpeg image and return it
            yield cv2.imencode('.jpg', img, Camera.encode_param)[1].tobytes()
