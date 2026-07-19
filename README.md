# 学习LVGL的小项目-桌面小摆件
  显示时间、天气、电脑的cpu温度、使用率、内存条的使用率等

## 这里就引出来多个难点：怎么获取天气，怎么获取电脑的硬件信息等
### 1.获取天气
从心知天气的api获得，这里又引出来一个问题，怎么获取当前的位置信息，难道多装一个gps定位嘛？
解决办法：一个通过ip获得当前城市的api
### 2.获取电脑硬件信息
可以直接用AIDA，它创建一个sse服务器，在同一个局域网内就能通过api获取对应服务器电脑信息了（这里的服务器就是你的电脑主机）
也可以自己开发：我就自己vibe coding了。它不只是能获取cpu温度、使用率、内存条的使用率信息，所有的硬件信息几乎都能通过这个软件查看（cpu型号等）
如果需要就从release中下载，注意，这是Windows系统的

## esp32端效果图：
<img width="1706" height="1279" alt="6c37128769d8e9a5986c00384be3b433" src="https://github.com/user-attachments/assets/2d06fd22-e4e0-428a-bdcc-a2dae6825a59" />

<img width="1279" height="1706" alt="f7008b93ad56cbce2e6fcfb5dbea5dbc" src="https://github.com/user-attachments/assets/0cdbdd4f-3323-4104-b30f-9e53c97e20ad" />

<img width="1706" height="1279" alt="8e001a7c9dfa58cc5c12b7927b753574" src="https://github.com/user-attachments/assets/61207379-ca86-4a3f-a30f-d65e71d91438" />

<img width="1279" height="1706" alt="78817cb35dceee67476040a703f71a85" src="https://github.com/user-attachments/assets/3f5a24fa-8372-4d40-9240-04f48a2519b9" />


硬件监控系统-SSE Server软件（Windows系统）

<img width="1637" height="1141" alt="image" src="https://github.com/user-attachments/assets/2554a75d-6185-457d-a22f-493982df1f6d" />

<img width="903" height="1226" alt="image" src="https://github.com/user-attachments/assets/2117c8b6-2912-4349-8c70-5aea0ca46bfa" />
