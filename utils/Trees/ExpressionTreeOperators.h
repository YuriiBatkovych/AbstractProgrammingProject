#ifndef ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONTREEOPERATORS_H
#define ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONTREEOPERATORS_H

#include "ExpTree.h"

template<typename TensorType,
        template<typename> class NodeCreatorClass>
ExpressionTree<TensorType, NodeCreatorClass>
operator+(const ExpressionTree<TensorType, NodeCreatorClass>& left,
          const ExpressionTree<TensorType, NodeCreatorClass>& right){

    ExpressionTree<TensorType, NodeCreatorClass> result;

    string op = "+";
    result.root = NodeCreatorClass<string>::create(op);
    result.root->set_left(NodeCreatorClass<string>::copy(*(left.root)));
    result.root->set_right(NodeCreatorClass<string>::copy(*(right.root)));

    return result;
}

template<typename TensorType,
        template<typename> class NodeCreatorClass>
ExpressionTree<TensorType, NodeCreatorClass>
operator*(const ExpressionTree<TensorType, NodeCreatorClass>& left,
          const ExpressionTree<TensorType, NodeCreatorClass>& right){

    ExpressionTree<TensorType, NodeCreatorClass> result;

    string op = "*";
    result.root = NodeCreatorClass<string>::create(op);
    result.root->set_left(NodeCreatorClass<string>::copy(*(left.root)));
    result.root->set_right(NodeCreatorClass<string>::copy(*(right.root)));

    return result;
}

template<typename TensorType,
        template<typename> class NodeCreatorClass>
ExpressionTree<TensorType, NodeCreatorClass>
operator/(const ExpressionTree<TensorType, NodeCreatorClass>& left,
          const ExpressionTree<TensorType, NodeCreatorClass>& right){

    ExpressionTree<TensorType, NodeCreatorClass> result;

    string op = "/";
    result.root = NodeCreatorClass<string>::create(op);
    result.root->set_left(NodeCreatorClass<string>::copy(*(left.root)));
    result.root->set_right(NodeCreatorClass<string>::copy(*(right.root)));

    return result;
}

template<typename TensorType,
        template<typename> class NodeCreatorClass>
ExpressionTree<TensorType, NodeCreatorClass>
operator-(const ExpressionTree<TensorType, NodeCreatorClass>& left,
          const ExpressionTree<TensorType, NodeCreatorClass>& right){

    ExpressionTree<TensorType, NodeCreatorClass> result;

    string op = "-";
    result.root = NodeCreatorClass<string>::create(op);
    result.root->set_left(NodeCreatorClass<string>::copy(*(left.root)));
    result.root->set_right(NodeCreatorClass<string>::copy(*(right.root)));

    return result;
}

#endif //ABSTRACTPROGRAMMINGPROJECT_EXPRESSIONTREEOPERATORS_H
