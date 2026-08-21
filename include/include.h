#ifndef INCLUDE_H
#define INCLUDE_H

void set_ip(int ip, FILE *program);
void render_display(char *option, int dpresx, int dpresy, bool displayfb[dpresy][dpresx]);
void render_display_ansi(int dpresy, int dpresx, bool displayfb[dpresy][dpresx]);
void render_display_unicode(int dpresy, int dpresx, bool displayfb[dpresy][dpresx]);

#endif
