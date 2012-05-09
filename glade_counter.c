#include <gtk/gtk.h>
#include <stdlib.h>

   /*����һ��ָ��GtkWidget���͵�ָ�루�����ı���ʹ�ã�*/
static GtkWidget *entry;

   /*����ȫ�ֱ���:��Ϊ��fnum����˫���ȣ���һ������������
                     ��snum����˫���ȣ��ڶ�����������*/
gdouble fnum = 0;
gdouble snum = 0;

   /*����ȫ�ֿ��Ʊ�������Ϊ��num_count�������ͣ���������λ������
                          ��operator�������ͣ����������������ţ���
                          ��first_num���������ͣ���������Ĵ�������
                          ��have_result��(�����ͣ�Ϊ���½��м�������׼��)*/
gint     num_count =0;
gint     operator = 0;
gboolean first_num = TRUE;
//gboolean first_num_equal = FALSE;
gboolean have_dot = FALSE; //С����
gboolean have_result = FALSE;
gchar    number[100];



/*........................................................................ */
//���������ClearReset����
//1�������Ļ�ϵ����ݣ�TURE��;2����ʼ��������������FALSE��

void ClearReset(gboolean clear_only)
        {
            /*��ʼ��number[100]�ȣ������ڴ�ռ�*/
            gint i = 0;
            for(i = 0;i<100;i++)
                number[i] = '\0';
            fnum = 0;
            snum = 0;
            operator = 0;
            num_count = 0;
            first_num = TRUE;
            have_dot = FALSE;
            have_result = FALSE;
            //first_num_equal = FALSE;

            /*�����Ļ*/
            if(clear_only = TRUE)
               gtk_entry_set_text(GTK_ENTRY(entry),"0");
            }       



/*---------------------------------------------------------------------------------- */
//��������ʱ�Ļص�������PressNum����

void PressNum(GtkButton *button,gpointer data)
        {
            /*����һ��ָ���ַ���ָ�������"num"(��������������)*/
            const gchar *num;             
            int i;
                                 
            /*�����������ֵ�λ��*/
            if(num_count == 9)
            return;
          
            /*����λ������*/
            num_count++;
          
            /*ͨ��button��label��ȡÿ���������ֵ���ַ����ͣ�*/
            num=gtk_button_get_label(GTK_BUTTON(button));
          
            /*g_strlcat() �����������ÿ���������֣��ַ��������ۼ�����*/
            i=g_strlcat(number,num,100);

                                
            /*�����һ�����͵ڶ������Ŀ��ƿ���,strtod()�ǰ��ַ���ת��Ϊgdouble��*/
            if(first_num )
            {
            /*��һ������*/
            fnum=strtod(number,NULL);

            }         
            else
            {
                    /*�ڶ�������*/
                    /*��ֹ����ʱ����Ϊ0*/
                    if(num_count == 1);
                    snum=strtod(number,NULL);
    
                    if(num_count == 1 && operator ==4 && snum == 0)
                    //gtk_entry_set_text(GTK_ENTRY(entry),"ERROR");
                    return;
            }

           if (number[0]=='0' && number[1]!='.' &&num_count>=2 )
            {
                   gint i;
               for (i =0 ; i<100; i++)
                   {   
                      number[i] = number[i+1];
                   }
            }
                  
            /*�������������ʾ����*/
            gtk_entry_set_text(GTK_ENTRY(entry),number);

            //g_print("F:%f\n",fnum);
            //g_print("S:%f\n",snum);

        }



/*----------------------------------------------------------------------------------*/
//����С����ʱ�Ļص�������PressDot����

void PressDot(GtkButton *button,gpointer data)
        {
           gint i;
            /*�ظ�������л�����*/
            if(have_result)
                ClearReset(FALSE);
              
            /*���С�����ڵ�һλ����ʾ*/
            if(num_count == 0)
             {
              ClearReset(TRUE);
             return;
             }
            /*��������С���������ʾ.have_dot��ֹ��������С����*/
           if(have_dot == FALSE)
                {
                    have_dot = TRUE;
                    i=g_strlcat(number,".",100);
                if(first_num)
                   /*��һ����������*/
                  fnum=strtod(number,NULL);
                else
                    {
                       /*�ڶ�����������*/
                      snum=strtod(number,NULL);
                       /*�������������ʾ����*/
                      gtk_entry_set_text(GTK_ENTRY(entry),number);
                    }
                
                }
        
        }



/*------------------------------------------------------------------------------------*/
//���������ʱ�Ļص�������PressClear����

void PressClear(GtkButton *button,gpointer data)
        {
            ClearReset(FALSE);
        }



/*------------------------------------------------------------------------------------*/
//���������ʱ�Ļص�������PressOperator����

void PressOperator(GtkButton *button,gpointer data)
        {
            gint i;
            switch(GPOINTER_TO_INT(data))
                        {
                            case 1: operator = 1;//�ӷ�
                            break;
                           
                            case 2: operator = 2;//����
                            break;
                           
                            case 3: operator = 3;//�˷�
                            break;
                          
                            case 4: operator = 4;//����
                            break;
                        }

            // g_print("F:%f\n",fnum);
            // g_print("S:%f\n",snum);

            /*�л�����ڶ�����*/
            first_num = FALSE;
            num_count = 0;
            have_dot =FALSE;
            for( i = 0;i<100;i++)
               number[i] = '\0';
        }


      
/*-------------------------------------------------------------------------------------*/
//���µ��ں�ʱ�Ļص�������PressEqual����
          
void PressEqual(GtkButton *button,gpointer data)
      {
            gdouble numb;
            gchar *result;
            gchar num[100];
            gint e = 0;
            g_print("F:%f\n",fnum);
            g_print("S:%f\n",snum);
            /*��������*/
            switch(operator)
                {
                    case 1: numb = fnum + snum ;
                             break;
                    case 2: numb = fnum - snum;
                             break;
                    case 3: numb = fnum * snum;
                             break;
                    case 4: numb = fnum / snum;
                             break;
               //��һ��ʼʲôҲ�������Ͱ�һ��= �ᵵ��������
                    default: gtk_entry_set_text(GTK_ENTRY(entry),number);
                             e = 1;
                             break;
               }

           if (e==0)
            {    /*�ѽ��ת�����ַ���*/
            result = g_ascii_dtostr(num,100,numb);
            fnum = numb;
            //������
            gtk_entry_set_text(GTK_ENTRY(entry),result);  
            have_result=TRUE;
          //first_num_equal = TRUE;
            }
          
         /*  
         result = g_ascii_dtostr(num,100,numb);
         fnum = numb;
         gtk_entry_set_text(GTK_ENTRY(entry),result);
         have_result=TRUE;
         first_num_equal = TRUE;     */

    }


/*-------------------------------------------------------------------------------------*/
//������:main()
int main(int argc,char* argv[])
        {
           /*����ָ��GtkWidget���͵�ָ��*/
            GtkWidget *window;
            GtkWidget *button;
            GtkWidget *vbox;
            GtkWidget *hbox;
            GtkWidget *table;
            GtkBuilder *builder = NULL;
            /*��ʼ��*/
            gtk_init(&argc,&argv);

            builder=gtk_builder_new();
            gtk_builder_add_from_file(builder,"counter.glade",NULL);
            gtk_builder_connect_signals(builder, NULL);
           // ���� ID ��ȡ�ӹ��� 
          window=GTK_WIDGET(gtk_builder_get_object(builder,"window")); 
          entry=GTK_ENTRY(gtk_builder_get_object(builder,"entry"));
            gtk_entry_set_text(GTK_ENTRY(entry),"0");
            gtk_editable_set_editable(GTK_EDITABLE(entry),FALSE);
            gtk_widget_set_direction(entry,GTK_TEXT_DIR_RTL);
         // text = GTK_LABEL(gtk_builder_get_object(builder, "label-main")); 

button=GTK_BUTTON(gtk_builder_get_object(builder, "button1")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressClear),NULL);
button=GTK_BUTTON(gtk_builder_get_object(builder, "button2")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button3")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button4")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button5")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressOperator),(gpointer)1);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button6")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button7")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button8")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button9")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressOperator),(gpointer)2);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button10")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button11")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button12")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button13")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressOperator),(gpointer)3);

button=GTK_BUTTON(gtk_builder_get_object(builder, "button14")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressNum),NULL);
button=GTK_BUTTON(gtk_builder_get_object(builder, "button15")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressDot),NULL);
button=GTK_BUTTON(gtk_builder_get_object(builder, "button16")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressEqual),NULL);
button=GTK_BUTTON(gtk_builder_get_object(builder, "button17")); 
          g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(PressOperator),(gpointer)4);
  
         // ��ȡ�� UI �����GtkBuilder ������û�����ã��ͷ��� 
  
         g_object_unref(G_OBJECT(builder)); 

                   
            gtk_widget_show_all(window);
            gtk_main();
            return 0;
        }