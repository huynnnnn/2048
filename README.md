# 2048
HƯỚNG DẪN CÀI ĐẶT
  - Sau khi clone về máy, truy cập vào thư mục chứa file main.cpp
  - Nhấn Shift + chuột phải, chọn Open PowerShell
  - gõ lệnh mingw32-make
  - gõ lệnh ./build/main.exe

MÔ TẢ
  - Cải tiến từ game 2048 cổ điển kích cỡ 4x4, người chơi có thể thay đổi size bảng 3x3 đến 10x10 một cách đơn giản
  - Trò chơi sử dụng bốn phím [UP], [DOWN], [LEFT], [RIGHT] để di chuyển và tạo thành số 2048

CÁC CHỨC NĂNG
  - Chọn kích cỡ bảng từ 3x3 đến 10x10
  - Lưu điểm và thời gian hiện tại
  - Quay lại một bước
  - New game và thoát
  - Có thông báo khi thắng hoặc thua
  - Video: https://youtu.be/wYjZYoveFM0

CÁC KỸ THUẬT LẬP TRÌNH
  - Sử dụng thư viện SDL2
  - Con trỏ 2 chiều
  - Xử lý các sự kiện từ bàn phím
  - Clip texture
  - Kỹ thuật check
  - Chia code thành các file: Game (xử lý khởi tạo, giải phóng bộ nhớ, chứa game loop, xử lý việc hiển thị ảnh và text), Move (chứa việc xử lý các sự kiện cũng như logic game), Function (xử lý việc hiển thị ảnh và text), gameCheck (kiểm tra điều kiện game), Board (xử lý bảng)
  - Cấu trúc, lớp: Xây dựng một số cấu trúc để lưu tọa độ (x và y)
  - Random để sinh ma trận số
  - Xử lý âm thanh
  - Xử lý thời gian 

KẾT LUẬN
  - Sau khi hoàn thành dự án game cuối kì này, em học được rất nhiều kiến thức và kinh nghiệm, từ tư duy code, cho đến việc lên ý tưởng, quản lý thời gian làm game.
- Điều tâm đắc: Đối với game, điều em tâm đắc nhất có lẽ là tự mình làm ra được 1 con game, 2048 cổ điển dù đã xuất hiện từ lâu và dù chưa thể hoàn thiện game nhưng cũng đã có thêm các tính năng mới như chọn kích cỡ của bảng và đi lại bước trước.
- Hướng phát triển: Nếu có thêm thời gian thì em muốn cải tiến đồ họa game, thêm các tính năng mới như tăng độ khó, tạo các menu, thêm phần save game dành cho nhiều người chơi để lưu điểm số,…
