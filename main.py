from flask import *
from flask_cors import CORS
import cv2
import numpy as np
from imageProcessing import get_char_from_image


app = Flask(__name__)
CORS(app)

char_set = [' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 'c', 't', '+', '{', 'i', '7', '?','u', '3', '0', 'p', 'w', '4', 'A', '8', 'D', 'X', '%', '#', 'H', 'W', 'M']


@app.route('/api/get-char', methods=['POST'])
def get_char():
    # try:
    image = request.files['file']
    image = cv2.imdecode(np.frombuffer(image.read(), np.uint8), cv2.IMREAD_COLOR)
    print(image)
    ans = get_char_from_image(image)
    return jsonify({'status': 'ok','data': ans})
    # except Exception as e:
    #     print(e)
    #     return jsonify({'error': 'Something went wrong'})


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0',port=5003)