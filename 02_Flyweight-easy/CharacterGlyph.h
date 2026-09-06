#pragma once
#include <iostream>

// ==================== 内部状态（共享部分） ====================
// 享元对象：存储可被多个上下文共享的不变数据
class CharacterGlyph {
public:
    CharacterGlyph(char symbol, std::string fontFamily, int fontSize)
        : symbol_(symbol)
        , fontFamily_(std::move(fontFamily))
        , fontSize_(fontSize)
    {
        // 模拟较重的初始化开销（如加载字形位图）
        std::cout << "[Create Flyweight] char='" << symbol_
                  << "' font=" << fontFamily_
                  << " size=" << fontSize_ << '\n';
    }
    // 外部状态通过参数传入，享元本身不持有外部状态
    void render(int x, int y) const {
        std::cout << "Render '" << symbol_ << "' ["
                  << fontFamily_ << ", " << fontSize_ << "] at ("
                  << x << ", " << y << ")\n";
    }
    char symbol() const noexcept { return symbol_; }
private:
    // 内部状态：不可变，可安全共享
    const char symbol_;
    const std::string fontFamily_;
    const int fontSize_;
};