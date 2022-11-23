#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct BSTNode{
    KeyType data;
    struct BSTNode *LChild;
    struct BSTNode *RChild;
}BSTNode,*BSTree;

//非递归的创建二叉排序树
int BST_insert(BSTree &Tree,KeyType value){
    BSTree new_tree_point=(BSTree)calloc(1,sizeof(BSTNode));//进来的新节点申请空间
    new_tree_point->data=value;//把值放入
    if(Tree==NULL){//树为空，新节点作为树根
        Tree=new_tree_point;
        return 0;
    }
    BSTree p=Tree,parent;//p用来查找树
    while(p){
        parent=p;//parent用来存p的父亲
        if(value>p->data){
            p=p->RChild;
        }else if(value<p->data){
            p=p->LChild;
        }else{
            return -1;//相等的元素不可以放入二叉排序树，考研不会考相同元素放入问题
        }
    }
    //接下来判断要放入parent的左孩子还是右孩子
    if(value>parent->data){
        parent->RChild=new_tree_point;
    }else{
        parent->LChild=new_tree_point;
    }
    return 0;
}

//王道书上递归的写法
int BST_insert1(BSTree &Tree,KeyType value){
    if(Tree==NULL){
        //为新节点申请空间，第一个节点作为树根，后面递归再进入的是叶子节点
        Tree=(BSTree)calloc(1,sizeof(BSTNode));
        Tree->data=value;
        return 1;//代表插入成功
    }else if(value==Tree->data){
        return 0;//发现相同元素就不插入
    }else if(value<Tree->data){
        return BST_insert1(Tree->LChild,value);
    }else{
        return BST_insert1(Tree->RChild,value);
    }
}

//王道书上没有二叉排序树删除代码，考研也没考大题
void delete_node(BSTree &Tree,KeyType value){
    if(Tree==NULL){
        return ;
    }
    if(value>Tree->data){
        delete_node(Tree->RChild,value);
    }else if(value<Tree->data){
        delete_node(Tree->LChild,value);
    }else{
        //找到了要删除的节点
        if(Tree->LChild==NULL){//左子树为空，右子树直接顶上去
            BSTree tempNode=Tree;
            Tree=Tree->RChild;
            free(tempNode);
        }else if(Tree->RChild==NULL){//右子树为空，左子树直接顶上去
            BSTree tempNode=Tree;
            Tree=Tree->LChild;
            free(tempNode);
        }else{//两边都不为空
              //一般的删除策略是左子树的最大数据或右子树的最小数据代替要删除的节点
              //这里采用排序左子树的最大数据来代替
            BSTree tempNode=Tree->LChild;
            while(tempNode->RChild!=NULL){//向右找到最大的
                tempNode=tempNode->RChild;
            }
            Tree->data=tempNode->data;
            delete_node(Tree->LChild,tempNode->data);//在左子树中找到要删除删除的值
        }
    }
}

void creat_BST(BSTree &Tree,KeyType *str,int len){
    for(int i=0;i<len;++i){
        BST_insert(Tree,str[i]);//把某一个节点放入二叉排序树
    }
}

void in_order(BSTree Tree){
    if(Tree!=NULL){
        in_order(Tree->LChild);
        printf("%3d",Tree->data);
        in_order(Tree->RChild);
    }
}

BSTree BST_search(BSTree Tree,KeyType value,BSTree &parent){
    parent=NULL;
    while(Tree!=NULL&&value!=Tree->data){
        parent=Tree;
        if(value<Tree->data){
            Tree=Tree->LChild;
        }else{
            Tree=Tree->RChild;
        }
    }
    return Tree;
}

int main(){
    BSTree Tree=NULL;//树根
    KeyType str[7]={54,20,66,40,28,79,58};
    creat_BST(Tree,str,7);
    in_order(Tree);
    printf("\n");

    BSTree search,parent;
    search=BST_search(Tree,40,parent);
    if(search){
        printf("找到了 %d\n",search->data);
    }else{
        printf("没找到\n");
    }

    delete_node(Tree,28);
    in_order(Tree);
    printf("\n");

    return 0;
}