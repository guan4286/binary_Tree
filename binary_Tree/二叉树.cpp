#include <iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

struct node
{
    // ������
    int data;

    // ��ڵ�
    node* lc;

    // �ҽ��
    node* rc;

    // ���캯��
    node()
        : data(0)
        , lc(NULL)
        , rc(NULL){}
    node(int x):data(x),lc(nullptr),rc(nullptr){}
    node(int x,node *ilc,node*irc):data(x),lc(ilc),rc(irc){}

};


// bst
class bstree
{
public:
    enum
    {
        hmax_size_32767 = 32767,
        hmin_size_0 = 0,
    };

public:

    // ���캯��
    bstree()
        : root(NULL)
        , size(0)
    {
    }

    // ��������
    virtual ~bstree() {}

    int get_size()
    {
        return size;
    }

    // ������
    void insert_node(int data)
    {
        int cur_size = get_size();
        cout << "cur_size = " << cur_size << endl;

        if (hmax_size_32767 == cur_size)
        {
            cout << "insert node error, the size of the tree is max" << endl;
            return;
        }
        root = insert(root, data);
    }
    // ������
    void insert_Natural(int data)
    {
        int cur_size = get_size();
        cout << "cur_size = " << cur_size << endl;

        if (hmax_size_32767 == cur_size)
        {
            cout << "insert node error, the size of the tree is max" << endl;
            return;
        }
        root = insertNatural(root, data);
    }
    

    // ���������ǰ�������-�ݹ鷨
    void pre_order()
    {
        pre_order_traverse(root);
    }
    // ���������ǰ�������-������
    void pre_order_iterator()
    {
        preorderTraversal(root);
    }

    // �������-�ݹ鷨
    void in_order()
    {
        in_order_traverse(root);
    }
    // �������-������
    void in_order_iterator()
    {
        inorderTraversal(root);
    }

    // �������-�ݹ鷨
    void post_order()
    {
        post_order_traverse(root);
    }
    // �������-������
    void post_order_iterator()
    {
        postorderTraversal(root);
    }

    //����������ֽй����������
    void Level_Order()
    {
        LevelOrder(root);
    }
    
    /*
        ����ĳ�����
        int key - ���ҽ��

        ����ֵ��
            NULL : ����ΪrootΪ�� ���� û���ҵ�
            != NULL, �ҵ����
    */
    node* query(int key)
    {
        if (NULL == root)
        {
            cout << "query error, root = null" << endl;
            return NULL;
        }

        return query_node(root, key);
    }

    // ɾ����
    void remove_all()
    {
        if (NULL == root)
        {
            cout << "remove all failed, root = null" << endl;
            return;
        }

        remove_all(root);

        int cur_size = get_size();
        if (0 == cur_size)
            root = NULL;
    }

    // ɾ��ĳ�����
    void remove_node(int del_data)
    {
        if (NULL == root)
        {
            cout << "remove node error, root = null" << endl;
            return;
        }

        node* parent_node = NULL;
        node* del_node = root;

        // �ҵ�ɾ�����ĸ��ڵ���ɾ�����
        while (del_node)
        {
            if (del_data == del_node->data)
                break;
            else if (del_data > del_node->data)
            {
                parent_node = del_node;
                del_node = del_node->rc;
            }
            else if (del_data < del_node->data)
            {
                parent_node = del_node;
                del_node = del_node->lc;
            }
        }

        // ��û���ҵ�Ҫɾ���Ľ��
        if (NULL == del_node)
        {
            cout << "remove node error, " << del_data << " was not find" << endl;
            return;
        }

        // 1����ɾ���Ľ��û����������������
        if ((NULL == del_node->lc) && (NULL == del_node->rc))
        {
            // ΪʲôҪ���жϸ���㣬��Ϊ�����ĸ��ڵ��Ҳ��������ΪNULL��
            // 1.1 ����ֻ��һ������㣬 ��root�ͷ�ֵΪ��
            if (del_node == root)
            {
                root = NULL;
                delete del_node;
                del_node = NULL;

                dec_size();
                return;
            }

            // 1.2 �Ǹ���㣬�Ǿ���Ҷ�ӽ���ˣ� �����ڵ�ָ��ɾ�����ķ�ָ֧��NULL
            if (del_node == parent_node->lc)
                parent_node->lc = NULL;
            else if (del_node == parent_node->rc)
                parent_node->rc = NULL;

            // �ͷŽ��
            delete del_node;
            del_node = NULL;
            dec_size();
        }

        // 2����ɾ�����ֻ�����ӣ�û���Һ���
        else if ((NULL != del_node->lc) && (NULL == del_node->rc))
        {
            // 2.1 ɾ�����Ϊ����㣬��ɾ���������������ǰɾ�����
            if (del_node == root)
            {
                root = root->lc;
            }
            // 2.2 ������㣬��ɾ������������Ϊ���ڵ������
            else
            {
                if (parent_node->lc == del_node)
                    parent_node->lc = del_node->lc;
                else if (parent_node->rc == del_node)
                    parent_node->rc = del_node->lc;
            }

            delete del_node;
            del_node = NULL;

            dec_size();
        }

        // 3����ɾ�����ֻ���Һ���
        else if ((NULL == del_node->lc) && (NULL != del_node->rc))
        {
            // 3.1 ��Ϊ�����
            if (root == del_node)
            {
                root = root->rc;
            }
            else
            {
                if (del_node == parent_node->lc)
                    parent_node->lc = del_node->rc;
                else if (del_node == parent_node->rc)
                    parent_node->rc = del_node->rc;
            }

            delete del_node;
            del_node = NULL;

            dec_size();
        }

        // 4����ɾ�����������ӣ������Һ���,��Ҫ�ҵ�ɾ�����ĺ�̽����Ϊ�����
        else if ((NULL != del_node->lc) && (NULL != del_node->rc))
        {
            node* successor_node = del_node->rc;
            parent_node = del_node;

            while (successor_node->lc)
            {
                parent_node = successor_node;
                successor_node = successor_node->lc;
            }

            // ������̽���뵱ǰɾ������������
            del_node->data = successor_node->data;
            // ��ָ���̽��ĸ��ڵ�ĺ������ú�̽���������
            if (successor_node == parent_node->lc)
                parent_node->lc = successor_node->rc;
            else if (successor_node == parent_node->rc)
                parent_node->rc = successor_node->rc;

            // ɾ����̽��
            del_node = successor_node;
            delete del_node;
            del_node = NULL;

            dec_size();
        }
    }

    // ������prootΪ��������С���
    node* get_min_node(node* proot)
    {
        if (NULL == proot->lc)
            return proot;

        return get_min_node(proot->lc);
    }

    // ������prooΪ���ڵ�������
    node* get_max_node(node* proot)
    {
        if (NULL == proot->rc)
            return proot;

        return get_max_node(proot->rc);
    }

    // ���ظ��ڵ�
    node* get_root_node()
    {
        return root;
    }

    // ����proot���ĸ��ڵ�
    node* get_parent_node(int key)
    {
        // ��ǰ���
        node* cur_node = NULL;
        // ���ڵ�
        node* parent_node = NULL;

        cur_node = root;

        // ����Ƿ��ҵ�
        bool is_find = false;
        while (cur_node)
        {
            if (key == cur_node->data)
            {
                is_find = true;
                break;
            }

            // ��Ϊ�ȵ�ǰ����ֵ��ҪС��������Ҫ���ҵ�ǰ����������
            else if (key < cur_node->data)
            {
                parent_node = cur_node;
                cur_node = cur_node->lc;
            }
            // ͬ�ϣ� ���ҵ�ǰ����������
            else if (key > cur_node->data)
            {
                parent_node = cur_node;
                cur_node = cur_node->rc;
            }
        }

        return (true == is_find) ? parent_node : NULL;
    }
    //��ȡ�������ĸ߶ȣ��ֽ����
    int get_Tree_height()
    {
        return _h;
    }
private:
    //����ĳ��ֵ
    node* query_node(node* proot, int key)
    {
        if (NULL == proot)
        {
            return proot;
        }

        if (proot->data == key)
            return proot;
        else if (proot->data > key)
        {
            return query_node(proot->lc, key);
        }
        else if (proot->data < key)
        {
            return query_node(proot->rc, key);
        }

        return NULL;
    }

    // �������ɾ�����н��
    void remove_all(node* proot)
    {
        if (NULL != proot)
        {
            remove_all(proot->lc);
            remove_all(proot->rc);
            delete proot;

            dec_size();
        }
    }

    // �������-�ݹ鷨
    void pre_order_traverse(node* proot)
    {
        if (NULL != proot)
        {
            cout << proot->data << ",   ";
            pre_order_traverse(proot->lc);
            pre_order_traverse(proot->rc);
        }
    }
    // �������-������
    vector<int> preorderTraversal(node* root) {
        vector<int> ret;
        if (root == nullptr) {
            return ret;
        }
        stack<node*> stk;
        node* p = root;
        while (p) {
            ret.push_back(p->data);
            stk.push(p);
            p = p->lc;
        }
        while (!stk.empty()) {
            p = stk.top();
            stk.pop();
            p = p->rc;
            while (p) {
                ret.push_back(p->data);
                stk.push(p);
                p = p->lc;
            }
        }
        return ret;
    }

    // �������-�ݹ鷨
    void in_order_traverse(node* proot)
    {
        if (NULL != proot)
        {
            in_order_traverse(proot->lc);
            cout << proot->data << ",   ";
            in_order_traverse(proot->rc);
        }
    }
    // �������-������
    vector<int> inorderTraversal(node* root) {
        vector<int> ret;
        if (root == nullptr) {
            return ret;
        }
        stack<node*> stk;
        node* p = root;
        while (p) {
            stk.push(p);
            p = p->lc;
        }
        while (!stk.empty()) {
            p = stk.top();
            stk.pop();
            ret.push_back(p->data);
            p = p->rc;
            while (p) {
                stk.push(p);
                p = p->lc;
            }
        }
        return ret;
    }

    // �������-�ݹ鷨
    void post_order_traverse(node* proot)
    {
        if (NULL != proot)
        {
            post_order_traverse(proot->lc);
            post_order_traverse(proot->rc);
            cout << proot->data << ",   ";
        }
    }
    // �������-������
    vector<int> postorderTraversal(node* root) {
        vector<int> ret;
        if (root == nullptr) {
            return ret;
        }
        node* p = root;
        stack<node*> stk;
        while (p) {
            stk.push(p);
            p = p->lc;
        }
        node* q = nullptr;
        while (!stk.empty()) {
            p = stk.top();
            if (p->rc == nullptr || p->rc == q) {
                ret.push_back(p->data);
                q = p;
                stk.pop();
                continue;
            }
            else {
                p = p->rc;
                while (p) {
                    stk.push(p);
                    p = p->lc;
                }
            }
        }
        return ret;
    }

    void LevelOrder(node* Tree) //�������_����ʵ�֣����е��ص����Ƚ��ȳ���
    {
        // �����������������߶�
        int hl = 0;
        int hr = 0;
        queue<node*> q;
        if (Tree != NULL)
            q.push(Tree);   //���ڵ������
        while (q.empty() == false)  //���в�Ϊ��
        {
            node* pnode = q.front();
            cout << pnode->data << " ";

            if (pnode->lc != NULL)   //��������ӣ����
            {
                q.push(pnode->lc);
                hl++;
            }

            if (pnode->rc != NULL)   //������Һ��ӣ����
            {
                q.push(pnode->rc);
                hr++;
            }
            q.pop();  //�Ѿ��������Ľڵ������

            // �������������ĸ߶ȣ���ȡĿǰ������ֵ��Ȼ�������һ�ֵļ���
            hl > hr ? (_h = hl) : (_h = hr);
        }
    }

    
    // ������
    node* insert(node* proot, int data)
    {
        // ��㲻���ڣ� �򴴽�
        if (NULL == proot)
        {
            //node* new_node = new(std::nothrow) node;
            proot = new(std::nothrow) node;
            if (NULL != proot)
            {
                proot->data = data;
                //proot = new_node;

                // ���+1��
                add_size();
            }
            //if (NULL != new_node)
            //{
            //    new_node->data = data;
            //    //proot = new_node;

            //    // ���+1��
            //    add_size();
            //}

            return proot;
        }

        //  ����ֵ�ȵ�ǰ���ֵ��ҪС�� ��Ӧ�ò��뵽��ǰ�ڵ����ߣ����Ƕ����������Ķ���
        if (proot->data > data)
        {
            proot->lc = insert(proot->lc, data);
        }
        // ����֮�ȵ�ǰ���ֵ��Ҫ����Ӧ�ò��뵽��ǰ�����ұ�
        else if (proot->data < data)
        {
            proot->rc = insert(proot->rc, data);
        }

        // ��ȣ��򲻲����㡣

        return proot;
    }


    //���ȽϽڵ��С����˳�������
    node* insertNatural(node* proot, int data)
    {
        // ��㲻���ڣ� �򴴽�
         // ��㲻���ڣ� �򴴽�
        if (NULL == proot)
        {
            //node* new_node = new(std::nothrow) node;
            proot = new(std::nothrow) node;
            if (NULL != proot)
            {
                proot->data = data;
                //proot = new_node;

                // ���+1��
                add_size();
            }
            return proot;

        }
        
        //  ����ֵ�ȵ�ǰ���ֵ��ҪС�� ��Ӧ�ò��뵽��ǰ�ڵ����ߣ����Ƕ����������Ķ���
        if (NULL == proot->lc)
        {
            proot->lc = insert(proot->lc, data);
        }
        // ����֮�ȵ�ǰ���ֵ��Ҫ����Ӧ�ò��뵽��ǰ�����ұ�
        else if (NULL == proot->rc)
        {
            proot->rc = insert(proot->rc, data);
        }

        // ��ȣ��򲻲����㡣

        return proot;
    }
    // size + 1
    void add_size()
    {
        if (hmax_size_32767 == size)
            return;
        size++;
    }

    // size - 1
    void dec_size()
    {
        if (hmin_size_0 == size)
        {
            return;
        }

        size--;
    }




private:
    // �����
    node* root;

    // ��ǰ���Ľ�����
    int size;

    int _h;
};

void updatavalue(const int * p)
{

}

// ���Դ���
int main()
{

    bstree tree;

    ////��б��
    //tree.insert_node(90);
    //tree.insert_node(70);

    //tree.insert_node(50);

    //tree.insert_node(30);
    //tree.insert_node(10);

    ////��б��
    //tree.insert_node(10);
    //tree.insert_node(20);
    //tree.insert_node(30);
    //tree.insert_node(40);
    //tree.insert_node(50);
    //tree.insert_node(60);

    //������������һ���ڵ�����ӽڵ��ֵ����С�ڸýڵ��ֵ�����ӽڵ��ֵ������ڸýڵ��ֵ
    /*
   ʾ�����ö�������
                 60
               /   \
             50     75
           /   \    /   
          40   55  70
                  /
                 65
*/
    tree.insert_node(60);
    tree.insert_node(50);
    tree.insert_node(75);

    tree.insert_node(70);
    tree.insert_node(40);
    tree.insert_node(65);
    tree.insert_node(55);


    ////��˳����룬���жϴ�С
    //tree.insert_Natural(60);
    //tree.insert_Natural(50);
    //tree.insert_Natural(70);
    //tree.insert_Natural(40);
    //tree.insert_Natural(65);
    //tree.insert_Natural(55);
    //tree.insert_Natural(75);
    //tree.insert_Natural(85);
    




    /*tree.insert_node(100);
    tree.insert_node(60);
    tree.insert_node(80);*/
    node * new_node = tree.query(55);
    if (NULL != new_node)
    {
        cout << "new_node = " << new_node->data << endl;


    }
    //�������
    cout << "�������" << endl;
    tree.Level_Order();
    cout << endl;
    int tree_height = tree.get_Tree_height();
    cout << "tree_height = " << tree_height << endl;
    // ǰ�����
    cout << "ǰ�����" << endl;
    tree.pre_order();
    cout << endl;

    // �������
    cout << "�������" << endl;
    tree.in_order();
    cout << endl;

    // �������
    cout << "�������" << endl;
    tree.post_order();
    cout << endl;

    //cout << "ɾ����㿪ʼ������������10086" << endl;

    //int del_key = 0;

    //while (true)
    //{
    //    cout << "����ɾ�����ֵ = ";
    //    cin >> del_key;
    //    if (10086 == del_key)
    //        break;

    //    tree.remove_node(del_key);

    //    cout << "ɾ����,������ = " << tree.get_size() << endl;
    //    cout << "ɾ���� ����������:";// << endl;
    //    tree.in_order();
    //    cout << endl << endl;
    //}

    //tree.remove_all();
    int s = 5;
    switch (++s)
    {
    case 6:
    case 7:s += 2;
    case 8:
    case 9:s += 2;
    }
    cout << "s = " << s << endl;

    int a = 1;
    int b = 3;
    const int* p = &a;
    a = 2;
    cout << "a = " << a << endl;
    //*p = &b;
    cout << "p = " << *p << endl;

    /// <summary>
    /// ////////////
    /// </summary>
    /// <returns></returns>
    double pi = 3.14;
    const double* cptr = &pi;
    pi = 4;

    return 0;
}