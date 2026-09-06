#pragma once
#include <memory>
#include "CharacterGlyph.h"
#include <mutex>
#include <unordered_map>
#include <string>

// ==================== 享元工厂 ====================
class GlyphFactory {
public:
    // 单例访问（线程安全，C++11 保证局部静态变量初始化线程安全）
    static GlyphFactory& instance() {
        static GlyphFactory factory;
        return factory;
    }
    // 获取或创建享元对象
    std::shared_ptr<CharacterGlyph> getGlyph(char symbol,
                                              const std::string& font,
                                              int size) {
        // 构造唯一 key
        std::string key = makeKey(symbol, font, size);
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = pool_.find(key);
        if (it != pool_.end()) {
            return it->second; // 命中缓存，直接复用
        }
        auto glyph = std::make_shared<CharacterGlyph>(symbol, font, size);
        pool_.emplace(std::move(key), glyph);
        return glyph;
    }
    size_t poolSize() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return pool_.size();
    }
private:
    GlyphFactory() = default;
    ~GlyphFactory() = default;
    GlyphFactory(const GlyphFactory&) = delete;
    GlyphFactory& operator=(const GlyphFactory&) = delete;
    static std::string makeKey(char symbol, const std::string& font, int size) {
        return std::string(1, symbol) + '_' + font + '_' + std::to_string(size);
    }
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::shared_ptr<CharacterGlyph>> pool_;
};