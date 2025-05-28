Git offers a variety of commands related to **branching**, each serving different purposes like creating, switching, listing, deleting, and managing branches. Here's a breakdown of the most commonly used Git branch-related commands:

---

### 🔧 **Creating Branches**

* `git branch <branch-name>`
  Creates a new branch, but does **not switch** to it.

* `git checkout -b <branch-name>`
  Creates a new branch and **switches** to it.

* `git switch -c <branch-name>` *(modern alternative to checkout)*
  Same as `git checkout -b`.

---

### 🔁 **Switching Between Branches**

* `git checkout <branch-name>`
  Switches to the specified branch.

* `git switch <branch-name>` *(preferred in modern Git)*
  Cleaner alternative to `checkout`.

---

### 📋 **Listing Branches**

* `git branch`
  Lists all **local** branches. Current branch is marked with `*`.

* `git branch -a`
  Lists **all branches**, local and remote.

---

### 🧹 **Deleting Branches**

* `git branch -d <branch-name>`
  Deletes a local branch (only if it's been fully merged).

* `git branch -D <branch-name>`
  Force deletes a branch, even if unmerged.

---

### ⬆️ **Pushing Branches to Remote**

* `git push origin <branch-name>`
  Pushes the branch to the remote repository.

* `git push --set-upstream origin <branch-name>`
  Pushes and sets the upstream (tracking) branch.

---

### 🔁 **Merging and Rebasing**

* `git merge <branch-name>`
  Merges the specified branch into your current branch.

* `git rebase <branch-name>`
  Reapplies commits on top of another base tip.

---

### 🔄 **Renaming Branches**

* `git branch -m <new-name>`
  Renames the current branch.

* `git branch -m <old-name> <new-name>`
  Renames a specified branch.

---

### 🔍 **Tracking and Remote Branches**

* `git branch -r`
  Lists remote branches only.

* `git branch --track <new-branch> <remote>/<branch>`
  Creates a local branch that tracks a remote branch.

---
