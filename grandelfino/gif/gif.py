from PIL import Image
import glob
import os

from matplotlib.pyplot import close

## ディレクトリの作成 ##

files = sorted(glob.glob('images/*.jpg'))
images = list(map(lambda file: Image.open(file), files))
images[0].save('GDF-17.gif', save_all=True,
               append_images=images[1:], duration=1.00, loop=0)
