/*
    BSD 3-Clause License
    
    Copyright (c) 2022, SudoCpp
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "TreeNode.hpp"
#include "Exception.hpp"

#define __class__ "simplex::TreeNode"

namespace simplex
{
        TreeNode::TreeNode(string name) : parent{nullptr}, ownedPointers{true}, name{name}, children{false} {}
        TreeNode::~TreeNode()
        {}
        
        TreeNode& TreeNode::getChild(int32_t index) const
        {
            if(children.size() > index)
                return *children[index];
            else
                throw IndexOutOfBoundsException("Index can not be greater than size of child node set.", __ExceptionParams__);
        }
        int32_t TreeNode::numberOfChildren() const
        {
            return children.size();
        }
        TreeNode& TreeNode::getParent() const
        {
            return *parent;
        }
        TreeNode& TreeNode::getRoot() const
        {
            if(parent != nullptr)
                return parent->getRoot();
            else
                return *parent;
        }
        TreeNode& TreeNode::nextSibling() const
        {
            int32_t index = parent->children.indexOf((TreeNode*)this);
            if(parent->children.size() > index)
                return *(parent->children[index+1]);
            else
                throw NullException("Parent does not exist.", __ExceptionParams__);
        }
        TreeNode& TreeNode::previousSibling() const
        {
            int32_t index = parent->children.indexOf((TreeNode*)this);
            if(index != 0)
                return *(parent->children[index-1]);
            else
                throw NullException("There is no previous node.", __ExceptionParams__);
        }

        bool TreeNode::parentExists() const
        {
            if(parent != nullptr)
                return true;
            else
                return false;
        }
        int32_t TreeNode::numberNextSiblings() const
        {
            return parent->children.size() - parent->children.indexOf((TreeNode*)this);
        }
        int32_t TreeNode::numberPreviousSiblings() const
        {
            return parent->children.indexOf((TreeNode*)this);
        }

        TreeNode& TreeNode::addChildNode(TreeNode* node, bool takeOnOwnership)
        {
            if(node != nullptr)
            {
                node->parent = this;
                children.add(node);
                if(takeOnOwnership)
                    ownedPointers.add(node);
                return *node;
            }
            else
                throw NullException("Unable to add node because it is a nullptr.", __ExceptionParams__);
            return *node;
        }

        int32_t TreeNode::getLevel() const
        {
            if(parent != nullptr)
                return parent->getLevel()+1;
            else
                return 0;
        }


        TreeNode* TreeNode::clone()
        {
            TreeNode* newNode = new TreeNode{name};
            for(TreeNode* child : children)
                newNode->addChildNode(child->clone(), true);
            return newNode;
        }
        void TreeNode::deleteNode()
        {
            if(parent != nullptr)
                parent->deleteChild(this);
            else
                delete this;                
        }
        TreeNode& TreeNode::deleteChild(TreeNode* childPtr)
        {
            removeChild(childPtr);
            if(ownedPointers.contains(childPtr))
                delete childPtr;
            return *this;
        }
        TreeNode* TreeNode::removeNode()
        {
            if(parent != nullptr)
                return parent->removeChild(this);
            else
                throw NullException("Unable to remove node from nullptr parent.", __ExceptionParams__);
        }
        TreeNode* TreeNode::removeChild(TreeNode* childPtr)
        {
            if(children.contains(childPtr))
                children.remove(childPtr, false);
            return childPtr;
        }
}

#undef __class__