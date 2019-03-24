/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */

/**
 * By BingLi224
 * 13:53 THA 23/03/2019
 */

void printout ( node * root ) {
    if ( ! root )
        return;
    
    cout << "[";
    
    if ( root->left )
        printout ( root->left );
    
    cout << root->val << ":" << root->ht;
    
    if ( root->right )
        printout ( root->right );
    
    cout << "]";
}

void updateHeight ( node * root ) {
    if ( root ) {
        updateHeight ( root->left );
        updateHeight ( root->right );
       
        root->ht = ( root->left ? root->left->ht : 0 ) - ( root->right ? root->right->ht : 0 );
    }
}

// self balancing
void selfBalance ( node *& root ) {
    if ( root ) {
        int l = ( root->left ? root->left->ht + 1 : 0 );
        int r = ( root->right ? root->right->ht + 1 : 0 );
        if ( l - r > 1 ) {
            // rotate at left side
            if ( ( root->left->left ? root->left->left->ht : -1 ) - ( root->left->right ? root->left->right->ht : -1 ) > 0 ) {
                node * temp = root->left;
                root->left = temp->right;
                temp->right = root;
                root = temp;

                // update the heights
                int l = 0, r = 0;
                if ( root->right->left )
                    l = root->right->left->ht + 1;
                if ( root->right->right )
                    r = root->right->right->ht + 1;
                root->right->ht = ( l > r ? l : r );
                root->ht = ( root->left->ht > root->right->ht ? root->left->ht + 1 : root->right->ht + 1 );
            } else {
                node * temp = root->left->right;
                root->left->right = temp->left;
                temp->left = root->left;

                root->left = temp->right;
                temp->right = root;
                root = temp;

                // update the heights
                int l, r;
                l = r = 0;
                if ( root->right->left )
                    l = root->right->left->ht + 1;
                if ( root->right->right )
                    r = root->right->right->ht + 1;
                root->right->ht = ( l > r ? l : r );
                l = r = 0;
                if ( root->left->left )
                    l = root->left->left->ht + 1;
                if ( root->left->right )
                    r = root->left->right->ht + 1;
                root->left->ht = ( l > r ? l : r );
                root->ht = ( root->left->ht > root->right->ht ? root->left->ht + 1 : root->right->ht + 1 );
            }
        } else if ( l - r < -1 ) { 
            // rotate at right side
            if ( ( root->right->left ? root->right->left->ht : -1 ) - ( root->right->right ? root->right->right->ht : -1 ) < 0 ) {
                node * temp = root->right;
                root->right = ( temp->left ? temp->left : nullptr );
                temp->left = root;
                root = temp;

                // update the heights
                int l = 0, r = 0;
                if ( root->left->left )
                    l = root->left->left->ht + 1;
                if ( root->left->right )
                    r = root->left->right->ht + 1;
                root->left->ht = ( l > r ? l : r );
                root->ht = ( root->left->ht > root->right->ht ? root->left->ht + 1 : root->right->ht + 1 );
            } else {
                node * temp = root->right->left;
                root->right->left = temp->right;
                temp->right = root->right;

                root->right = temp->left;
                temp->left = root;
                root = temp;

                // update the heights
                int l, r;
                l = r = 0;
                if ( root->right->left )
                    l = root->right->left->ht + 1;
                if ( root->right->right )
                    r = root->right->right->ht + 1;
                root->right->ht = ( l > r ? l : r );
                l = r = 0;
                if ( root->left->left )
                    l = root->left->left->ht + 1;
                if ( root->left->right )
                    r = root->left->right->ht + 1;
                root->left->ht = ( l > r ? l : r );
                root->ht = ( root->left->ht > root->right->ht ? root->left->ht + 1 : root->right->ht + 1 );
            }
        } else {
            root->ht = ( l > r ? l : r );
        }
    }
}

void insert_recursive ( node *& root, int val ) {
    if ( ! root ) {
        root = new node { val, NULL, NULL, 0 };
        return;
    }
    
	if ( val < root->val ) {
        // if empty
        if ( root->left ) {
            insert_recursive ( root->left, val );
            root->ht = 1 + root->left->ht;
        } else {
            root->left = new node { val, NULL, NULL, 0 };
            root->ht = 1;
        }

        if ( root->right && root->ht < root->right->ht + 1 )
            root->ht = 1 + root->right->ht;
    } else {
        // if empty
        if ( root->right ) {
            insert_recursive ( root->right, val );
            root->ht = root->right->ht + 1;
        } else {
            root->right = new node { val, NULL, NULL, 0 };
            root->ht = 1;
        }
        
        if ( root->left && root->ht < root->left->ht + 1 )
            root->ht = 1 + root->left->ht;
    }

    selfBalance ( root );
}

node * insert(node * root, int val)
{
    insert_recursive ( root, val );
    return root;
}
