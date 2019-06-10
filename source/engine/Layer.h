#ifndef LAYER_H
#define LAYER_H

class Layer{
public:
    Layer();
    Layer(int layer);
    ~Layer();

    void Register(int layer);
    void Unregister(int layer);

    int GetMask();

    bool Intersect(int layer);
    bool Intersect(Layer& layer);

    bool Match(int layer);
    bool Match(Layer& layer);
private:
    int m_layerMask;
};

#endif // !LAYER_H