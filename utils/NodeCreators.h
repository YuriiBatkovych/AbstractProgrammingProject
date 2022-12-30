#ifndef ABSTRACTPROGRAMMINGPROJECT_NODECREATORS_H
#define ABSTRACTPROGRAMMINGPROJECT_NODECREATORS_H

#include "ComputeNode.h"
#include "VectorNode.h"
#include "FunctionalNode.h"

template<typename Tensor>
class TreeNodeCreator{
public:
    static TreeNode<Tensor>* create(){
        return new TreeNode<Tensor>();
    }

    static TreeNode<Tensor>* create(Tensor& val){
        return new TreeNode<Tensor>(val);
    }
};

template<typename Tensor>
class ComputeNodeCreator{
public:
    static ComputeNode<Tensor>* create(){
        return new ComputeNode<Tensor>();
    }

    static ComputeNode<Tensor>* create(Tensor& val){
        return new ComputeNode<Tensor>(val);
    }
};


template<typename Tensor>
class VectorNodeCreator{
public:
    static VectorNode<Tensor>* create(){
        return new VectorNode<Tensor>();
    }

    static VectorNode<Tensor>* create(Tensor& val){
        return new VectorNode<Tensor>(val);
    }
};


template<typename Tensor>
class FunctionalNodeCreator{
public:
    static FunctionalNode<Tensor>* create(){
        return new FunctionalNode<Tensor>();
    }

    static FunctionalNode<Tensor>* create(Tensor& val){
        return new FunctionalNode<Tensor>(val);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_NODECREATORS_H