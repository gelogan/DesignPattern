#pragma once
#include <iostream>
#include "GlyphFactory.h"
#include "TextDocument.h"
int main(int, char**){
    TextDocument doc;
    // 模拟排版一段文本，多次出现相同字符/字体/字号组合
    doc.addChar('H', "Arial", 12, 0, 0);
    doc.addChar('e', "Arial", 12, 10, 0);
    doc.addChar('l', "Arial", 12, 20, 0);
    doc.addChar('l', "Arial", 12, 30, 0); // 复用 'l' 的享元
    doc.addChar('o', "Arial", 12, 40, 0);
    doc.addChar('H', "Arial", 12, 0, 20); // 复用 'H' 的享元
    doc.addChar('e', "Times", 14, 10, 20); // 不同字体，新建享元
    doc.render();
    std::cout << "\nTotal Flyweight objects created: "
              << GlyphFactory::instance().poolSize() << '\n';
    // 输出应为 5（H, e@Arial, l, o, e@Times），而非 7 次请求
    std::cout << "Hello, from DesignPatterns!\n";
    return 0;
}
