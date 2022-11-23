#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct BSTNode{
    KeyType data;
    struct BSTNode *LChild;
    struct BSTNode *RChild;
}BSTNode,*BSTree;

//�ǵݹ�Ĵ�������������
int BST_insert(BSTree &Tree,KeyType value){
    BSTree new_tree_point=(BSTree)calloc(1,sizeof(BSTNode));//�������½ڵ�����ռ�
    new_tree_point->data=value;//��ֵ����
    if(Tree==NULL){//��Ϊ�գ��½ڵ���Ϊ����
        Tree=new_tree_point;
        return 0;
    }
    BSTree p=Tree,parent;//p����������
    while(p){
        parent=p;//parent������p�ĸ���
        if(value>p->data){
            p=p->RChild;
        }else if(value<p->data){
            p=p->LChild;
        }else{
            return -1;//��ȵ�Ԫ�ز����Է�����������������в��ῼ��ͬԪ�ط�������
        }
    }
    //�������ж�Ҫ����parent�����ӻ����Һ���
    if(value>parent->data){
        parent->RChild=new_tree_point;
    }else{
        parent->LChild=new_tree_point;
    }
    return 0;
}

//�������ϵݹ��д��
int BST_insert1(BSTree &Tree,KeyType value){
    if(Tree==NULL){
        //Ϊ�½ڵ�����ռ䣬��һ���ڵ���Ϊ����������ݹ��ٽ������Ҷ�ӽڵ�
        Tree=(BSTree)calloc(1,sizeof(BSTNode));
        Tree->data=value;
        return 1;//�������ɹ�
    }else if(value==Tree->data){
        return 0;//������ͬԪ�ؾͲ�����
    }else if(value<Tree->data){
        return BST_insert1(Tree->LChild,value);
    }else{
        return BST_insert1(Tree->RChild,value);
    }
}

//��������û�ж���������ɾ�����룬����Ҳû������
void delete_node(BSTree &Tree,KeyType value){
    if(Tree==NULL){
        return ;
    }
    if(value>Tree->data){
        delete_node(Tree->RChild,value);
    }else if(value<Tree->data){
        delete_node(Tree->LChild,value);
    }else{
        //�ҵ���Ҫɾ���Ľڵ�
        if(Tree->LChild==NULL){//������Ϊ�գ�������ֱ�Ӷ���ȥ
            BSTree tempNode=Tree;
            Tree=Tree->RChild;
            free(tempNode);
        }else if(Tree->RChild==NULL){//������Ϊ�գ�������ֱ�Ӷ���ȥ
            BSTree tempNode=Tree;
            Tree=Tree->LChild;
            free(tempNode);
        }else{//���߶���Ϊ��
              //һ���ɾ����������������������ݻ�����������С���ݴ���Ҫɾ���Ľڵ�
              //��������������������������������
            BSTree tempNode=Tree->LChild;
            while(tempNode->RChild!=NULL){//�����ҵ�����
                tempNode=tempNode->RChild;
            }
            Tree->data=tempNode->data;
            delete_node(Tree->LChild,tempNode->data);//�����������ҵ�Ҫɾ��ɾ����ֵ
        }
    }
}

void creat_BST(BSTree &Tree,KeyType *str,int len){
    for(int i=0;i<len;++i){
        BST_insert(Tree,str[i]);//��ĳһ���ڵ�������������
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
    BSTree Tree=NULL;//����
    KeyType str[7]={54,20,66,40,28,79,58};
    creat_BST(Tree,str,7);
    in_order(Tree);
    printf("\n");

    BSTree search,parent;
    search=BST_search(Tree,40,parent);
    if(search){
        printf("�ҵ��� %d\n",search->data);
    }else{
        printf("û�ҵ�\n");
    }

    delete_node(Tree,28);
    in_order(Tree);
    printf("\n");

    return 0;
}