#include "COBBTree.hpp"


namespace urde
{
/* This is exactly what retro did >.< */
u32 verify_deaf_babe(CInputStream& in)
{
    return in.readUint32Big();
}

/* This is exactly what retro did >.< */
u32 verify_version(CInputStream& in)
{
    return in.readUint32Big();
}

COBBTree::COBBTree(const SIndexData& indexData, const CNode* root)
    : x18_indexData(indexData),
      x88_root((CNode*)root)
{
}

COBBTree::COBBTree(CInputStream& in)
    : x0_magic(verify_deaf_babe(in)),
      x4_version(verify_version(in)),
      x8_memsize(in.readUint32()),
      x18_indexData(in),
      x88_root(new CNode(in))
{
}

zeus::CAABox COBBTree::CalculateLocalAABox() const
{
    return CalculateAABox(zeus::CTransform::Identity());
}

zeus::CAABox COBBTree::CalculateAABox(const zeus::CTransform& xf) const
{
    if (x88_root)
        return x88_root->GetOBB().calculateAABox(xf);
    return zeus::CAABox::skInvertedBox;
}

COBBTree::SIndexData::SIndexData(CInputStream& in)
{
    u32 count = in.readUint32Big();
    x0_.reserve(count);
    for (u32 i = 0 ; i < count ; i++)
        x0_.push_back(in.readUint32Big());

    count = in.readUint32Big();
    for (u32 i = 0 ; i < count ; i++)
        x10_.push_back(in.readUByte());
    count = in.readUint32Big();
    for (u32 i = 0 ; i < count ; i++)
        x20_.push_back(in.readUByte());
    count = in.readUint32Big();
    for (u32 i = 0 ; i < count ; i++)
        x30_.push_back(in.readUByte());

    count = in.readUint32Big();
    for (u32 i = 0 ; i < count ; i++)
        x40_.push_back(in);

    count = in.readUint32Big();
    for (u32 i = 0 ; i < count ; i++)
        x50_.push_back(in.readUint16Big());

    count = in.readUint32Big();
    for (u32 i = 0 ; i < count ; i++)
        x60_.push_back(zeus::CVector3f::ReadBig(in));
}

COBBTree::CNode::CNode(const zeus::CTransform& xf, const zeus::CVector3f& point,
                       const COBBTree::CNode* left, const COBBTree::CNode* right,
                       const COBBTree::CLeafData* leaf)
    : x0_obb(xf, point),
      x3c_isLeaf(leaf != nullptr)
{
    x40_left.reset((CNode*)left);
    x44_right.reset((CNode*)right);
    x48_leaf.reset((CLeafData*)leaf);
}

COBBTree::CNode::CNode(CInputStream& in)
{
    x0_obb = zeus::COBBox::ReadBig(in);
    x3c_isLeaf = in.readBool();
    if (x3c_isLeaf)
        x48_leaf.reset(new CLeafData(in));
    else
    {
        x40_left.reset(new CNode(in));
        x44_right.reset(new CNode(in));
    }
}

COBBTree::CNode* COBBTree::CNode::GetLeft() const
{
    return x40_left.get();
}

COBBTree::CNode*COBBTree::CNode::GetRight() const
{
    return x44_right.get();
}

COBBTree::CLeafData*COBBTree::CNode::GetLeafData() const
{
    return x48_leaf.get();
}

const zeus::COBBox& COBBTree::CNode::GetOBB() const
{
    return x0_obb;
}

size_t COBBTree::CNode::GetMemoryUsage() const
{
    size_t ret = 0;
    if (x3c_isLeaf)
        ret = x48_leaf->GetMemoryUsage() + 80;
    else
    {
        if (x40_left)
            ret = x40_left->GetMemoryUsage() + 80;
        if (x44_right)
            ret += x44_right->GetMemoryUsage();
    }

    if (!(ret & 3))
        return ret;

    return ret + ((ret & 3) - 4);
}

COBBTree::CLeafData::CLeafData(const std::vector<u16>& surface)
    : x0_surface(surface)
{
}

const std::vector<u16>& COBBTree::CLeafData::GetSurfaceVector() const
{
    return x0_surface;
}

size_t COBBTree::CLeafData::GetMemoryUsage() const
{
    size_t ret = (x0_surface.size() * 2) + 16;
    if (!(ret & 3))
        return ret;
    return ret + ((ret & 3) - 4);
}

COBBTree::CLeafData::CLeafData(CInputStream& in)
{
    u32 edgeCount = in.readUint32Big();
    for (u32 i = 0 ; i < edgeCount ; i++)
        x0_surface.push_back(in.readUint16Big());
}

}
