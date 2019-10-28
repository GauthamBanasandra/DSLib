package UFDS;

public class Ufds {
    public Ufds(int numNodes) {
        mNumNodes = numNodes;
        mRank = new int[mNumNodes];
        mParentIndex = new int[mNumNodes];

        for (int i = 0; i < mNumNodes; i++) {
            mParentIndex[i] = i;
        }
    }

    public int findSet(int i) {
        if (mParentIndex[i] == i) {
            return i;
        }

        mParentIndex[i] = findSet(mParentIndex[i]);
        return mParentIndex[i];
    }

    public boolean isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    public void unionSet(int i, int j) {
        if (isSameSet(i, j)) {
            return;
        }

        int iParent = findSet(i);
        int jParent = findSet(j);
        if (mRank[iParent] > mRank[jParent]) {
            mParentIndex[jParent] = iParent;
        } else {
            mParentIndex[iParent] = jParent;
            if (mRank[iParent] == mRank[jParent]) {
                ++mRank[jParent];
            }
        }
    }

    private final int mNumNodes;
    private int[] mParentIndex;
    private int[] mRank;
}
