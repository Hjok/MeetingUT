#include "matriceinteret.h"
#include "QDebug"
MatriceInteret::MatriceInteret(QObject *parent):QAbstractTableModel(parent)
{

}
//Fonctions d'implémentation de modèle
/*!
 * \brief MatriceInteret::rowCount calcule le nombre de lignes de la matrice
 * \param parent
 * \return le nombre de groupes
 */
int MatriceInteret::rowCount(const QModelIndex &parent) const
{

    return matrice.size();
}
/*!
 * \brief MatriceInteret::columnCount calcule le nombre de colonnes de la matrice
 * \param parent
 * \return le nombre de groupes
 */
int MatriceInteret::columnCount(const QModelIndex &parent) const
{
    return matrice.size();
}
/*!
 * \brief MatriceInteret::data fournit les données au tableau
 * \param index l'index ligne/colonne de la valeur demandée
 * \param role le rôle (lecture, écriture, ...)
 * \return la valeur d'interet
 */
QVariant MatriceInteret::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(obtenirIndex(index.row()) && obtenirIndex(index.column()))
            return matrice[obtenirIndex(index.row())][obtenirIndex(index.column())];
    }
    return QVariant();

}
/*!
 * \brief MatriceInteret::headerData fournit l'en-tête des lignes et colonnes
 * \param section l'index de la ligne ou de la colonne
 * \param orientation si il s'agit d'une ligne ou d'une colonne
 * \param role le role (lecture, ecriture, ...)
 * \return
 */
QVariant MatriceInteret::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(obtenirIndex(section))
            return obtenirIndex(section)->obtenirNom();
    }
    return QVariant();
}
/*!
 * \brief MatriceInteret::setData met à jour la valeur indiquée
 * \param index l'index de la valeur à mettre à jour
 * \param value la nouvelle valeur
 * \param role le role
 * \return true si réussite
 */
bool MatriceInteret::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        if(obtenirIndex(index.row()) && obtenirIndex(index.column()))
        {
            matrice[obtenirIndex(index.row())][obtenirIndex(index.column())] = value.toInt();
            emit valeurChangee();
        }
    }
    return true;
}
/*!
 * \brief MatriceInteret::flags régle les détails
 * \return
 */
Qt::ItemFlags MatriceInteret::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

//Les fonctions propre à la classe
/*!
 * \brief MatriceInteret::obtenirInteretsId retourne les interet qu'un groupe trouve chez les les autres
 * \param _groupe
 * \return une map avec en indice l'id des groupes et en valeur l'interet
 */
QMap<int, int> MatriceInteret::obtenirInteretsId (const Groupe *_groupe)const
{
    QMap<const Groupe*, int>::const_iterator j;
    QMap<int, int> liste;
    for(j=matrice[_groupe].begin(); j!= matrice[_groupe].end(); ++j)
    {
        liste[j.key()->obtenirId()]=j.value();
    }

    return liste;
}
/*!
 * \brief MatriceInteret::definirInteret définit l'interet entre deux groupe
 * \param _g1 le groupe acteur de l'interet
 * \param _g2 le groupe objet de l'interet
 * \param _interet la valeur de l'interet
 */
void MatriceInteret::definirInteret(const Groupe *_g1, const Groupe *_g2, unsigned int _interet)
{
    //Par défaut on considère que les groupes sont déjà contenus dans la matrice
    //Et qu'il ne faut donc pas créer de nouvelle ligne ou colonne dans la vue
    bool nouvCol=false;
    bool nouvLigne=false;
    //Si le groupe acteur n'est pas une clé de la map, on crée une nouvelle ligne
    if(!matrice.contains(_g1))
        nouvLigne=true;
    //Si le groupe objet n'est pas une clé de la sous-map, on crée une nouvelle colonne
    if(matrice.size()<=1 || !matrice.begin().value().contains(_g2))
        nouvCol=true;
    //On crée les nouvelles lignes/colonnes si nécessaires
    if(nouvLigne)
        beginInsertRows(QModelIndex(), 0, 0);
    if(nouvCol)
        beginInsertColumns(QModelIndex(), 0, 0);

    //On définit la nouvelle valeur
    matrice[_g1][_g2] = _interet;

    //On crée l'index du tableau correspondant à la valeur modifiée
    QModelIndex index =createIndex(obtenirPlace(_g1), obtenirPlace(_g2));
    //Et on signale à la vue que cette valeur a changé
    emit dataChanged(index, index);

    //On termine le processsus d'insertion de nouvelles lignes/colonnes si il existait
    if(nouvLigne)
        endInsertRows();
    if(nouvCol)
        endInsertColumns();
}
/*!
 * \brief MatriceInteret::retirerGroupe retire un groupe du modèle et le répercute sur la vue
 * \param _g le groupe à retirer
 */
void MatriceInteret::retirerGroupe(const Groupe *_g)
{
    QMap<const Groupe*, QMap<const Groupe*, int>>::const_iterator j;
    //On signale qu'on va retirer une ligne et une colonne
    beginRemoveRows(QModelIndex(), obtenirPlace(_g), obtenirPlace(_g));
    beginRemoveColumns(QModelIndex(), obtenirPlace(_g), obtenirPlace(_g));

    QModelIndex index;
    //On retire le groupe de la map contenant tous ses interets
    matrice.remove(_g);
    int i=0;
    int k=obtenirPlace(_g);
    //Puis on retir le groupe des maps qui contiennent les interets des autres groupes
    for(j=matrice.begin(); j!= matrice.end(); ++j)
    {
        //On indique que la case i, k qui a été supprimée plus haut a été changée
        index =createIndex(i, k);
        emit dataChanged(index, index);
        //On supprime l'interet du groupe courant pour le groupe à supprimer
        matrice[j.key()].remove(_g);

        //Et on signale le changemant à la vue
        index =createIndex(k, i);
        emit dataChanged(index, index);

        i++;
    }
    //On finit le retrait de la ligne et de la colonne
    endRemoveColumns();
    endRemoveRows();
}
/*!
 * \brief MatriceInteret::obtenirIndex retourn le groupe corespondant à l'index du tableau
 * \param _index l'index du groupe qu'on veut obtenir
 * \return le groupe cherché
 */
const Groupe* MatriceInteret::obtenirIndex(int _index) const
{
    QMap<const Groupe*, QMap<const Groupe*, int>>::const_iterator j;
    int i=0;
    for(j=matrice.begin(); j!= matrice.end(); ++j)
    {
        if(i== _index)
            return j.key();
        i++;
    }
    return NULL;
}
/*!
 * \brief MatriceInteret::obtenirPlace retourne la place du groupe dans le tableau
 * \param _g le groupe dont on veut ttrouver la place
 * \return l'index dans le tableau
 */
int MatriceInteret::obtenirPlace(const Groupe *_g) const
{
    QMap<const Groupe*, QMap<const Groupe*, int>>::const_iterator j;
    int i=0;
    for(j=matrice.begin(); j!= matrice.end(); ++j)
    {
        if(j.key()==_g)
            return i;
        i++;
    }
    return -1;
}
