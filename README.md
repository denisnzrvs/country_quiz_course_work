# country_quiz_course_work

### System requirements
- portaudio
`brew install portaudio`

### Installing
`./configure && make` in `/libs/portaudio/`

### Compiling
To test sound: `g++ -Wall -Wextra -g3 ./sound.cpp -o ./output/sound -lportaudio`
To compile main.cpp and other needed files: `g++ -std=c++11 main.cpp menu.cpp -o country_quiz`