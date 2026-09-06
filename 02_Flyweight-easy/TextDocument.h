#pragma once
#include "GlyphFactory.h"
#include <vector>

// ==================== 客户端上下文（外部状态） ====================
// 持有享元引用 + 外部状态（位置信息不属于享元）
struct CharacterContext {
    std::shared_ptr<CharacterGlyph> glyph; // 共享的享元
    int x, y;                              // 外部状态
    void render() const {
        glyph->render(x, y);
    }
};
// ==================== 客户端调用 ====================
class TextDocument {
public:
    void addChar(char c, const std::string& font, int size, int x, int y) {
        auto glyph = GlyphFactory::instance().getGlyph(c, font, size);
        chars_.push_back({glyph, x, y});
    }
    void render() const {
        for (const auto& ctx : chars_) {
            ctx.render();
        }
    }
private:
    std::vector<CharacterContext> chars_;
};