# rtsp-
rtsp学习
## rtsp_client
* 简单发送rtsp命令，不涉及具体rtp数据传输
* windows下vs2015 编译运行

## rtsp_server/rtsp_server.c
* 简单接收rtsp命令，不涉及具体rtp数据传输
* linux环境下编译：gcc rtsp_server.c.运行./a,out后，可接收rtsp命令，并打印出来

## rtp_h264
* 简单rtp数据包发送，不涉及rtsp命令
* linux环境下编译：gcc rtp.c rtp_h264.c
* 运行./a,out后，程序开始发送rtp数据包，可通过vlc接收（不含音频）


## rtsp_ffmpeg
* 利用ffmpeg库对rtsp数据源录像的完整程序
* windows下vs2015 编译运行，请使用debug模式，release模式需自己配置参数，才能编译通过
