# 🥢🎱 Mini Billiard

## 🔖 Description
This project was designed for a practical assignment for the subject “3D Programming”, which consists of creating a scene with a table and billiard balls, using the contents of OpenGL with VAOs, VBOs, EBOs/IBOs, Shaders, etc.., and then applying collisions and animations to the balls to simulate a shot.

## ⌨️ Keys
The keys are very simple, here is a list of the keys that is being listened:
* **Mouse - Left Click + Drag**: To rotate the camera depending on which side you are dragging.
* **Mouse Scroll**: To change the zoom of the scene.
* **Space**: To animate a random ball.
* **Key 1**: To enable/disable the ambient light.
* **Key 2**: To enable/disable the directional light.
* **Key 3**: To enable/disable the point light.
* **Key 4**: To enable/disable the spot light.

## 🕹 Images & Videos
![1](https://github.com/0rangeFox/Mini-Billiard/assets/38193239/4d3aeb86-7ef6-40f0-9476-b3637258c6e7)
![2](https://github.com/0rangeFox/Mini-Billiard/assets/38193239/de622baf-dd4c-48da-9497-ca0e47c889df)

https://github.com/0rangeFox/Mini-Billiard/assets/38193239/3a283b31-495c-4041-aae9-47d96de16b36

## ⚙️ How to build the project
```bash
git clone https://github.com/0rangeFox/Mini-Billiard.git
cd Mini-Billiard
git submodule update --init
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make && sudo make install
```

## 📝 License
Copyright © 2024 [João Fernandes](https://github.com/0rangeFox) & [Tiago Mendes](https://github.com/mendes001). <br/>
This project is [MIT](LICENSE) licensed.
