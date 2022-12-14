//
// Created by Adarion on 2022/11/4.
//

#ifndef ERISU_ENGINE_UICOMPONENT_H
#define ERISU_ENGINE_UICOMPONENT_H

#include "IUIComponent.h"
#include "../../../Render/GLTexture.h"
#include "Global/Global.h"
#include "library/Vector.h"

namespace Erisu::Function
{
    class UIContainer;

    enum class UIAnchor
    {
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

    enum class BlendMode
    {
        Alpha,
        Additive,
        Multiply,
        Screen,
        Overlay,
        Darken,
        Lighten,
        Disabled
    };

    void ApplyBlendMode(BlendMode mode);

    // NOTICE: UIComponent is a base class for all UI components
    // UIComponent's transform is not depend on its parent GameObject's transform
    class UIComponent : public IUIComponent
    {
    public:
        UIAnchor Anchor = UIAnchor::MiddleCenter;
        BlendMode AlphaBlend = BlendMode::Alpha;

    private:
        using Vec2 = Scripts::Vector2;
        using Vec3 = Scripts::Vector3;
        using Vec4 = Scripts::Vector4;

    protected:
        bool visible_ = true;
        int priority_ = 0;

        float rotation_ = 0.0f;
        Eigen::Vector4f rect_ = {0, 0, 0, 0}; // x, y, width, height
        Eigen::Vector4f color_ = {1.0f, 1.0f, 1.0f, 1.0f};
        Eigen::Vector2f scale_ = {1.0f, 1.0f};

        std::weak_ptr<UIContainer> parent_ = std::weak_ptr<UIContainer>();

    public:
        Eigen::Vector2f GetAnchorOffset() const;

    protected:
        virtual Eigen::Matrix4f GetModelMatrix() const;
        virtual Eigen::Matrix4f GetProjectionMatrix() const;

    public:
        explicit UIComponent(std::string name, int priority = 0) : IUIComponent(std::move(name)), priority_(priority)
        {}

        ~UIComponent() override = default;

        bool IsVisible() override
        { return visible_; }

        void SetVisible(bool visible) override
        { this->visible_ = visible; }

        int GetPriority() const override
        { return priority_; }

        virtual void SetPriority(int priority)
        { this->priority_ = priority; }

        float& GetRotation()
        { return rotation_; }

        virtual void SetRotation(float rotation)
        { this->rotation_ = rotation; }

        Eigen::Vector4f& GetColor()
        { return color_; }

        virtual void SetColor(const Eigen::Vector4f &color)
        { this->color_ = color; }

        Eigen::Vector4f& GetRect()
        { return rect_; }

        virtual void SetRect(const Eigen::Vector4f &rect)
        { this->rect_ = rect; }

        virtual void SetRect(float x, float y, float width, float height)
        { this->rect_ = {x, y, width, height}; }

        virtual void SetPosition(float x, float y)
        {
            this->rect_.x() = x;
            this->rect_.y() = y;
        }

        virtual void SetOnScreenPosition(float x, float y);

        virtual Eigen::Vector2f GetPosition() const
        { return {this->rect_.x(), this->rect_.y()}; }

        virtual void SetSize(float width, float height)
        {
            this->rect_.z() = width;
            this->rect_.w() = height;
        }

        Eigen::Vector2f GetSize() const
        { return {this->rect_.z(), this->rect_.w()}; }

        Eigen::Vector2f& GetScale()
        { return scale_; }

        virtual void SetScale(const Eigen::Vector2f &scale)
        { this->scale_ = scale; }

        virtual void SetScale(float x, float y)
        { this->scale_ = {x, y}; }

        void SetParent(const std::shared_ptr<UIContainer> &parent)
        { this->parent_ = parent; }

        Eigen::Vector2f GetScreenPosition() const;

        bool IsPointInRect(const Eigen::Vector2f &point) const;

    public:
        // For Javascript

        Vec2* GetPositionJs() const
        { return new Vec2{this->rect_.x(), this->rect_.y()}; }

        void SetPositionJs(const Vec2 &position)
        { this->SetPosition(position.x, position.y); }

        Vec2* GetSizeJs() const
        { return new Vec2{this->rect_.z(), this->rect_.w()}; }

        void SetSizeJs(const Vec2 &size)
        { this->SetSize(size.x, size.y); }

        Vec2* GetScaleJs() const
        { return new Vec2{this->scale_.x(), this->scale_.y()}; }

        void SetScaleJs(const Vec2 &scale)
        { this->SetScale(scale.x, scale.y); }

        Vec4* GetColorJs() const
        { return new Vec4{this->color_.x(), this->color_.y(), this->color_.z(), this->color_.w()}; }

        void SetColorJs(const Vec4 &color)
        { this->SetColor({color.x, color.y, color.z, color.w}); }

        Vec4* GetRectJs() const
        { return new Vec4{this->rect_.x(), this->rect_.y(), this->rect_.z(), this->rect_.w()}; }

        void SetRectJs(const Vec4 &rect)
        { this->SetRect(rect.x, rect.y, rect.z, rect.w); }

        Vec2* GetScreenPositionJs() const
        { auto pos = this->GetScreenPosition(); return new Vec2 {pos.x(), pos.y()}; }

        bool IsPointInRectJs(const Vec2 &point) const
        { return this->IsPointInRect({point.x, point.y}); }

        void SetOnScreenPositionJs(const Vec2 &position)
        { this->SetOnScreenPosition(position.x, position.y); }


        void SetAnchorJs(const std::string &anchor)
        {
            if (anchor == "TopLeft")
                this->Anchor = UIAnchor::TopLeft;
            else if (anchor == "TopCenter")
                this->Anchor = UIAnchor::TopCenter;
            else if (anchor == "TopRight")
                this->Anchor = UIAnchor::TopRight;
            else if (anchor == "MiddleLeft")
                this->Anchor = UIAnchor::MiddleLeft;
            else if (anchor == "MiddleCenter")
                this->Anchor = UIAnchor::MiddleCenter;
            else if (anchor == "MiddleRight")
                this->Anchor = UIAnchor::MiddleRight;
            else if (anchor == "BottomLeft")
                this->Anchor = UIAnchor::BottomLeft;
            else if (anchor == "BottomCenter")
                this->Anchor = UIAnchor::BottomCenter;
            else if (anchor == "BottomRight")
                this->Anchor = UIAnchor::BottomRight;
        }

        std::string GetAnchorJs() const
        {
            switch (this->Anchor)
            {
                case UIAnchor::TopLeft:
                    return "TopLeft";
                case UIAnchor::TopCenter:
                    return "TopCenter";
                case UIAnchor::TopRight:
                    return "TopRight";
                case UIAnchor::MiddleLeft:
                    return "MiddleLeft";
                case UIAnchor::MiddleCenter:
                    return "MiddleCenter";
                case UIAnchor::MiddleRight:
                    return "MiddleRight";
                case UIAnchor::BottomLeft:
                    return "BottomLeft";
                case UIAnchor::BottomCenter:
                    return "BottomCenter";
                case UIAnchor::BottomRight:
                    return "BottomRight";
                default:
                    return "TopLeft";
            }
        }

        Vec2* GetAnchorOffsetJs() const
        { auto offset = this->GetAnchorOffset(); return new Vec2{offset.x(), offset.y()}; }

        void AddToUIObjectJs();

        void SetBlendModeJs(const std::string &blendMode)
        {
            if (blendMode == "Alpha")
                this->AlphaBlend = BlendMode::Alpha;
            else if (blendMode == "Add")
                this->AlphaBlend = BlendMode::Additive;
            else if (blendMode == "Multiply")
                this->AlphaBlend = BlendMode::Multiply;
            else if (blendMode == "Screen")
                this->AlphaBlend = BlendMode::Screen;
            else if (blendMode == "Overlay")
                this->AlphaBlend = BlendMode::Overlay;
            else if (blendMode == "Darken")
                this->AlphaBlend = BlendMode::Darken;
            else if (blendMode == "Lighten")
                this->AlphaBlend = BlendMode::Lighten;
            else if (blendMode == "Disabled")
                this->AlphaBlend = BlendMode::Disabled;
            else
                LOG_ERROR("Unknown blend mode: " + blendMode);
        }

        void SetEnabledJs(bool enabled_)
        { this->enabled = enabled_; }

    public:
        void Update() override
        {}

        void Render() override
        {
            // if you use UIComponent directly, it just as a rect which be used to receive input
        }

        void ShowInInspector() override;
    };
}

#include "../Component/UIContainer.h"

#endif //ERISU_ENGINE_UICOMPONENT_H
