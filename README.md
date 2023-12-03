# country_quiz_course_work

### System requirements
- portaudio
`brew install portaudio`

### Installing
`./configure && make` in `/libs/portaudio/`

### Compiling
To test sound: `g++ -Wall -Wextra -g3 ./sound.cpp -o ./output/sound -lportaudio`
To compile main.cpp and other needed files: `g++ main.cpp menu.cpp -o myprogram`