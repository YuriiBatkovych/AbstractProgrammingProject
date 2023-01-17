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

    static TreeNode<Tensor>* copy(const TreeNode<Tensor>& val){
        return new TreeNode<Tensor>(val);
    }
};

template<typename Tensor>
class ComputeNodeCreator : public TreeNodeCreator<Tensor>{
public:
    static ComputeNode<Tensor>* create(){
        return new ComputeNode<Tensor>();
    }

    static ComputeNode<Tensor>* create(Tensor& val){
        return new ComputeNode<Tensor>(val);
    }

    static ComputeNode<Tensor>* copy(const TreeNode<Tensor>& val){
        return new ComputeNode<Tensor>(val);
    }
};


template<typename Tensor>
class VectorNodeCreator : public TreeNodeCreator<Tensor>{
public:
    static VectorNode<Tensor>* create(){
        return new VectorNode<Tensor>();
    }

    static VectorNode<Tensor>* create(Tensor& val){
        return new VectorNode<Tensor>(val);
    }

    static VectorNode<Tensor>* copy(const TreeNode<Tensor>& val){
        return new VectorNode<Tensor>(val);
    }
};


template<typename Tensor>
class FunctionalNodeCreator : public TreeNodeCreator<Tensor>{
public:
    static FunctionalNode<Tensor>* create(){
        return new FunctionalNode<Tensor>();
    }

    static FunctionalNode<Tensor>* create(Tensor& val){
        return new FunctionalNode<Tensor>(val);
    }

    static FunctionalNode<Tensor>* copy(const TreeNode<Tensor>& val){
        return new FunctionalNode<Tensor>(val);
    }
};

#endif //ABSTRACTPROGRAMMINGPROJECT_NODECREATORS_H
