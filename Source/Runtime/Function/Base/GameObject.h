//
// Created by Adarion on 2022/9/16.
//
#pragma once
#ifndef ERISU_ENGINE_GAMEOBJECT_H
#define ERISU_ENGINE_GAMEOBJECT_H

#include <string>
#include <deque>
#include "Transform.h"
#include "../Render/Shader/GLShader.h"
#include "Camera.h"
#include "Light.h"
#include "Log/LogSystem.h"

namespace Erisu::Function
{
    class Scene;
    class IComponent;

    class GameObject : public std::enable_shared_from_this<GameObject>
    {
    protected:
        friend class Scene;
        virtual void SetScene(const std::shared_ptr<Scene> &scene);

    protected:
        int64_t id_;

        std::weak_ptr<GameObject> parent_ {};
        std::weak_ptr<Scene> scene_ {};

        std::string name_;
        // use container which iterator is available after insertion or deletion
        std::list<std::shared_ptr<GameObject>> children_;
        std::list<std::shared_ptr<IComponent>> components_;

        int64_t currentId = 0;
        bool currentIsDestroyed = false;

        Transform transform_;

    public:
        bool Enabled = true;
    public:
        explicit GameObject(std::string name);

        virtual ~GameObject();

        void SetName(const std::string &name);

        void SetParent(const std::shared_ptr<GameObject> &parent);
        void AddChild(const std::shared_ptr<GameObject> &child);
        void RemoveChild(const std::shared_ptr<GameObject> &child);

        virtual void Update();
        virtual void Render();

        void AddComponent(const std::shared_ptr<IComponent> &component);

        template<class T, class ...TParm>
        std::shared_ptr<T> AddComponent(TParm &&...parm);

        void Destroy();

        void RemoveComponent(const std::shared_ptr<IComponent> &component);

        Eigen::Matrix4f GetModelMatrix() const;
        Eigen::Vector3f GetWorldPosition() const;

        [[nodiscard]] std::shared_ptr<IComponent> GetComponent(const std::string &) const;
        [[nodiscard]] std::list<std::shared_ptr<IComponent>> & GetAllComponents();

        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] std::weak_ptr<GameObject> GetParent() const;
        [[nodiscard]] std::list<std::shared_ptr<GameObject>> GetChildren() const;

        [[nodiscard]] int64_t GetId() const;
        [[nodiscard]] Transform &GetTransform();
        
    };

    template<class T, class... TParm>
    std::shared_ptr<T> GameObject::AddComponent(TParm &&... parm)
    {
        auto component = std::make_shared<T>(std::forward<TParm>(parm)...);
        component->SetGameObject(shared_from_this());

        if (!scene_.expired())
            component->SetScene(scene_.lock());

        components_.push_back(component);
        return component;
    }


}
#endif //ERISU_ENGINE_GAMEOBJECT_H
