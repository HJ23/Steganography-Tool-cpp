#include "endecoder.cpp"


int main() {


    std::string text = "Here is Your Secret Message !";
    encoder *b = new encoder(text, "./Results/football.jpg");
    b->start();
    b->save("./Results/dec-football.png");

    decoder *a = new decoder("./Results/dec-football.png");
    a->start();
    a->show();

    delete a;
    delete b;

}
