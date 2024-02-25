all : b2cy.c b2cl.c

b2cy.c : b2cy.y
        bison b2cy.y -o b2cy.c -d
b2cl.c : b2cl.l b2cy.h
        flex -i b2cl.l
        rename lex.yy.c b2cl.c
clean:
        vrm b2cl.c b2cy.h b2cy.c


