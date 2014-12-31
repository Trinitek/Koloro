gource -s 5 --key -1280x720 -o .\gourceout.ppm -r 60
ffmpeg -y -r 60 -f image2pipe -vcodec ppm -i gourceout.ppm -vcodec libx264 gourcevid.mp4
