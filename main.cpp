#include <cassert>
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* MakeList(const std::vector<int>& numbers) {
  ListNode* head = nullptr;
  for (auto iter = numbers.rbegin(); iter != numbers.rend(); ++iter) {
    head = new ListNode{*iter, head};
  }

  return head;
}

class Solution {
 public:
  /**
   * Constraints:
   * The number of nodes in the list is sz.
   * 1 <= sz <= 30
   * 0 <= Node.val <= 100
   * 1 <= n <= sz
   */
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    // FIXME
    return nullptr;
  }
};

void AssertEq(ListNode* lhs, ListNode* rhs) {
  while (lhs) {
    assert(rhs);
    assert(lhs->val == rhs->val);
    lhs = lhs->next;
    rhs = rhs->next;
  }
}

void TestRemoveNthFromEnd() {
  Solution s;
  {
    auto head = MakeList({1,2,3,4,5});
    head = s.removeNthFromEnd(head, 2);
    AssertEq(MakeList({1,2,3,5}), head);
  }
  {
    auto head = MakeList({1});
    head = s.removeNthFromEnd(head, 1);
    assert(head == nullptr);
  }
}

int main() {
  TestRemoveNthFromEnd();
  std::cout << "Ok!" << std::endl;
  return 0;
}
