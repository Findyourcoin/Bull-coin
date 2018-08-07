// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_ENCRYPTDECRYPT_H
#define BITCOIN_QT_ENCRYPTDECRYPT_H

#include "walletmodel.h"

#include <QStackedWidget>


#include <QDialog>
#include <QString>


class ClientModel;
class WalletModel;
class PlatformStyle;

namespace Ui {
    class EncryptDecryptDialog;
}

/**
 * A single entry in the dialog for sending bitcoins.
 * Stacked widget, with different UIs for payment requests
 * with a strong payee identity.
 */
class EncryptDecryptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EncryptDecryptDialog(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~EncryptDecryptDialog();

    void setClientModel(ClientModel *clientModel);
    void setModel(WalletModel *model);

    bool validate();
    SendCoinsRecipient getValue();

    /** Return whether the entry is still empty and unedited */
    bool isClear();

    void setValue(const SendCoinsRecipient &value);
    void setAddress(const QString &address);

    /** Set up the tab chain manually, as Qt messes up the tab chain by default in some cases
     *  (issue https://bugreports.qt-project.org/browse/QTBUG-10907).
     */
    QWidget *setupTabChain(QWidget *prev);

    void setFocus();

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void removeEntry(EncryptDecryptDialog *entry);
    void payAmountChanged();
    void subtractFeeFromAmountChanged();

private Q_SLOTS:
    void deleteClicked();
    void on_payTo_textChanged(const QString &address);
    void on_addressBookButton_clicked();
    void on_pasteButton_clicked();
    void on_chooserButton_clicked();
    void updateDisplayUnit();

private:
    SendCoinsRecipient recipient;
    Ui::EncryptDecryptDialog *ui;
    ClientModel *clientModel;
    WalletModel *model;
    const PlatformStyle *platformStyle;

    bool updateLabel(const QString &address);
};

#endif // BITCOIN_QT_ENCRYPTDECRYPT_H