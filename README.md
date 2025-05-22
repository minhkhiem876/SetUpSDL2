# 🐤 Game Flappy Bird

*Tên:* Nguyễn Minh Khiêm
*Mã sinh viên:* 24021534
*Ngưỡng điểm mong muốn:* 8.0

---

## 🎮 Giới thiệu

Đây là phiên bản đơn giản của game Flappy Bird do mình xây dựng bằng ngôn ngữ C++ và thư viện đồ họa SDL2. Người chơi điều khiển chú chim bay qua các ống bằng cách nhấn phím cách. Nếu va vào ống hoặc rơi xuống đất, trò chơi kết thúc.

Ngoài ra, game còn có thêm vật phẩm xuất hiện ngẫu nhiên (tỉ lệ 50%). Khi ăn được vật phẩm, người chơi sẽ được tăng điểm.

---

## ⚙️ Các tính năng đã cài

### 🎯 Gameplay

* Chim bay lên khi nhấn phím cách, rơi xuống do trọng lực.
* Ống được sinh ra liên tục với khoảng cách và vị trí ngẫu nhiên.
* Vật phẩm xuất hiện ngẫu nhiên (50% tỉ lệ), tăng điểm khi ăn được.
* Kiểm tra va chạm giữa chim và ống/đất để xác định điều kiện thua.

### 🎨 Đồ họa & Animation

* Dùng SDL2 để vẽ nền, chim, ống, vật phẩm.
* Animation cho chim khi bay và khi chết.
* Hiển thị điểm số bằng SDL\_ttf, rõ ràng và dễ nhìn.
* Menu với giao diện đơn giản, dễ dùng.

---


## 🌟 Điểm nổi bật

* Animation sinh động cho chim và hiệu ứng khi chết.
* Có hệ thống vật phẩm ngẫu nhiên giúp tăng điểm.
* Menu có setting điều chỉnh độ khó – một điểm cộng cho khả năng mở rộng game.
* Giao diện đơn giản nhưng đầy đủ, mượt mà nhờ SDL2.

---

## 📚 Tài liệu tham khảo

* Các video tutorial về SDL2 trên YouTube.
* Tham khảo các video phân tích gameplay Flappy Bird để hiểu cơ chế điểm, vật lý và độ khó.

---

## 🤖 Mức độ sử dụng AI

* Dùng AI để tham khảo cách xử lý input và logic va chạm.
* Hỏi AI khi gặp lỗi liên quan đến SDL2 hoặc muốn tối ưu animation.
* Viết README với sự hỗ trợ của AI, sau đó chỉnh sửa để phù hợp với nội dung thực tế của game.
