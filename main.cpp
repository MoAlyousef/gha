#define FL_INTERNALS

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/platform.H>
#include <X11/Xlib.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>

class Fl_Gtk_Container : public Fl_Window {
  long other_xid_ = 0;
  GtkWidget *win_ = NULL;

public:
  Fl_Gtk_Container(int x, int y, int w, int h, const char *title = 0)
      : Fl_Window(x, y, w, h, title) {}

  void add(GtkWidget *win) {
    win_ = win;
    auto gdk_win = gtk_widget_get_window(GTK_WIDGET(win));
    other_xid_ = GDK_WINDOW_XID(gdk_win);
    XReparentWindow(fl_display, other_xid_, fl_xid(this), x(), y());
    XFlush(fl_display);
    Fl::add_idle([](void *) { gtk_main_iteration(); });
  }
};

GtkWidget *create_gtk_win(int argc, char **argv) {
  gtk_init(&argc, &argv);
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *btn = gtk_button_new_with_label("Hello World");
  gtk_window_set_default_size(GTK_WINDOW(win), 200, 200);
  gtk_container_add(GTK_CONTAINER(win), btn);
  gtk_widget_show_all(win);
  return win;
}

int main(int argc, char **argv) {
  auto main_win = new Fl_Window(400, 300);
  auto wv_win = new Fl_Gtk_Container(5, 5, 390, 290);
  main_win->end();
  main_win->show();

  auto gtk_win = create_gtk_win(argc, argv);
  wv_win->add(gtk_win);

  return Fl::run();
}
