int InizializzaGriglia()
{
    for(unsigned int r=0;r<R;++r)
    {
        for(unsigned int c=0;c<C;++c)
        {
            Griglia[r][c][0]=' ';
            Griglia[r][c][1]=' ';
            Griglia[r][c][2]=' ';
        }
    }
    return 0;
}

int ImpostaLivelli()
{
    //  Moltiplicatori di lettere singole
    for(unsigned int r=0;r<R;++r)
    {
        for(unsigned int c=0;c<C;++c)
        {
            if(((r==0 || r==R-1) && (c==4 || c==C-5)) || ((r==4 || r==R-5) && (c==0 || c==C-1)) || ((r==2 || r==R-3) && (c==(int)(C/2)+1 || c==(int)(C/2)-1)) || ((c==2 || c==C-3) && (r==(int)(R/2)+1 || r==(int)(R/2)-1)) || (r==(int)(R/2) && (c==3 || c==C-4)) || (c==(int)(C/2) && (r==3 || r==R-4)) || ((c==(int)(C/2)+1 || c==(int)(C/2)-1) && (r==(R/2)-1 || r==(R/2)+1)))
            {
                Griglia[r][c][1]='2';
            }
            else if(((r==1 || r==R-2) && (c==(int)(C/2)-2 || c==(int)(C/2)+2)) || ((r==(int)(R/2)+2 || r==(int)(R/2)-2) && (c==1 || c==C-2 || c==(int)(C/2)-2 || c==(int)(C/2)+2)))
            {
                Griglia[r][c][1]='3';
            }
            else if((r==0 || r==R-1 || (r==(int)(R/2) && c!=(int)(C/2))) && (c==0 || c==(int)(C/2) || c==C-1))
            {
                Griglia[r][c][2]='3';
            }
            else if((r==c || r==C-c-1) && r!=0 && r!=(int)(R/2)+1 && r!=(int)(R/2)-1 && r!=(int)(R/2)-2 && r!=(int)(R/2)+2 && r!=(int)(R/2))
            {
                Griglia[r][c][2]='2';
            }
        }
    }

    return 0;
}

void FinestraPrincipale::VisualizzaScarabei()
{

    // Visualizzazione degli scarabei

    if(Jolly[0]!=' ')
    {
        QString ScarA="";
        ScarA=ScarA+Jolly[0];
        ui->Scar1->setText(ScarA);
    }

    if(Jolly[1]!=' ')
    {
        QString ScarB="";
        ScarB=ScarB+Jolly[1];
        ui->Scar2->setText(ScarB);
    }
}
