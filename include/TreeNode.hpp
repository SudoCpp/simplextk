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

#ifndef SIMPLEX_TREENODE_HPP
#define SIMPLEX_TREENODE_HPP

#include "string.hpp"
#include "Array.hpp"

namespace simplex
{
    class TreeNode : public object
    {
        TreeNode* parent;
        Array<TreeNode*> ownership;

        public:
        Array<TreeNode*> children;

        TreeNode(string name);
        virtual ~TreeNode();
        virtual TreeNode& getChild(int32_t index) const;
        int32_t numberOfChildren() const;
        //Go one level up
        virtual TreeNode& getParent() const;
        //Go to the root of the whole tree.
        virtual TreeNode& getRoot() const;

        virtual TreeNode& nextSibling() const;
        virtual TreeNode& previousSibling() const;

        bool parentExists() const;

        int32_t numberNextSiblings() const;
        int32_t numberPreviousSiblings() const;

        virtual TreeNode& addChildNode(const string& name);
        //Ownership can not be taken for objects created on the stack
        virtual TreeNode& addChildNode(TreeNode* node, bool takeOnOwnership);

        int32_t getLevel() const;

        //Clones this TreeNode and all children
        virtual TreeNode* clone();
        //Delete this TreeNode and all children, returns parent
        void deleteNode();
        //Delete child node
        virtual TreeNode& deleteChild(TreeNode* childPtr);
        //Remove this TreeNode from Parent (must have a parent)
        virtual TreeNode* removeNode();
        //Remove a child from parent and return it's address
        virtual TreeNode* removeChild(TreeNode* childPtr);

        string name;
    };
}

#endif //SIMPLEX_TREENODE_HPP