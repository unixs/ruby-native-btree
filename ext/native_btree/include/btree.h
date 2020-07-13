#include <string>
#include <ruby.h>
#include <glib.h>

using namespace std;

class BTree {
  public:
    BTree(VALUE comparator);
    ~BTree();

    // get
    VALUE const &operator[](VALUE key) const;
    // set
    void operator[](VALUE key);

    gint
    height();

    gint
    size();

    bool
    del(VALUE key);

    void
    clear();

    bool
    has(VALUE key);

    void
    mark();

    void
    set(VALUE key, VALUE value);

    VALUE
    get(VALUE key);

  private:
    GTree *tree;
    VALUE comparator;

    void
    markMyRValues();

    static gint
    nativeComparator(gconstpointer keyA, gconstpointer keyB, gpointer tree);

    static gint
    markRValue(gpointer key, gpointer value, gpointer not_used);
};

