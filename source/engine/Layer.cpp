#include "Layer.h"

#define assert(x) 
//if (!x) throw 1;

Layer::Layer(){
    m_layerMask = 0;
}

Layer::Layer(int layer){
    m_layerMask = 0;

    Register(layer);
}

Layer::~Layer(){
}

void Layer::Register(int layer){
    assert(layer>=0 && layer < 32);

    m_layerMask = m_layerMask | (1 << layer);
}
void Layer::Unregister(int layer){
    assert(layer>=0 && layer < 32);

    m_layerMask = m_layerMask ^ (1 << layer);
}

int Layer::GetMask(){
    return m_layerMask;
}

bool Layer::Intersect(int layer){
    assert(layer>=0 && layer < 32);

    return m_layerMask & (1 << layer);
}
bool Layer::Intersect(Layer& layer){
    return m_layerMask & layer.GetMask();

}

bool Layer::Match(int layer){
    assert(layer>=0 && layer < 32);

    return m_layerMask == (1 << layer);
}
bool Layer::Match(Layer& layer){
    return m_layerMask == layer.GetMask();
}