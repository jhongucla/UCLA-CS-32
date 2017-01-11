void listAll(string path, const File* f)  // two-parameter overload
{
    path = path + "/" + f->name();
    cout << path << endl;
    if (f->files() == NULL)
        return;
    for (int i = 0; i < f->files()->size(); i++)
        listAll(path, f->files()->at(i));
}