#include <gtk/gtk.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080

GtkWidget *log_view;
GtkWidget *ip_entry;
GtkWidget *packet_buttons[6]; // 5 packets + send all
GtkWidget *scroll;
int sock = -1;

// === Utility: log messages into TextView ===
void log_message(const char *msg) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(log_view));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, msg, -1);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);

    // Auto-scroll to bottom
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll));
    gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj));
}

// === Enable/Disable packet buttons ===
void set_packet_buttons_sensitive(gboolean state) {
    for (int i = 0; i < 6; i++) {
        gtk_widget_set_sensitive(packet_buttons[i], state);
    }
}

// === Individual Packet Functions ===
void send_packet21(GtkWidget *w, gpointer d) {
    if (sock < 0) { log_message("❌ Not connected!"); return; }
    unsigned char packet[5] = {0xBB,0x01,0x02,0x21,0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    log_message("➡ Sent Packet 21");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        char logbuf[512] = "⬅ Reply 21: ";
        for (int i=0;i<valread;i++){ char tmp[8]; snprintf(tmp,8,"%02X ",buffer[i]); strcat(logbuf,tmp);}
        log_message(logbuf);
    }
}
void send_packet22(GtkWidget *w, gpointer d) {
    if (sock < 0) { log_message("❌ Not connected!"); return; }
    unsigned char packet[5] = {0xBB,0x01,0x02,0x22,0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    log_message("➡ Sent Packet 22");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        char logbuf[512] = "⬅ Reply 22: ";
        for (int i=0;i<valread;i++){ char tmp[8]; snprintf(tmp,8,"%02X ",buffer[i]); strcat(logbuf,tmp);}
        log_message(logbuf);
    }
}
void send_packet23(GtkWidget *w, gpointer d) {
    if (sock < 0) { log_message("❌ Not connected!"); return; }
    unsigned char packet[5] = {0xBB,0x01,0x02,0x23,0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    log_message("➡ Sent Packet 23");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        char logbuf[512] = "⬅ Reply 23: ";
        for (int i=0;i<valread;i++){ char tmp[8]; snprintf(tmp,8,"%02X ",buffer[i]); strcat(logbuf,tmp);}
        log_message(logbuf);
    }
}
void send_packet24(GtkWidget *w, gpointer d) {
    if (sock < 0) { log_message("❌ Not connected!"); return; }
    unsigned char packet[5] = {0xBB,0x01,0x02,0x24,0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    log_message("➡ Sent Packet 24");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        char logbuf[512] = "⬅ Reply 24: ";
        for (int i=0;i<valread;i++){ char tmp[8]; snprintf(tmp,8,"%02X ",buffer[i]); strcat(logbuf,tmp);}
        log_message(logbuf);
    }
}
void send_packet25(GtkWidget *w, gpointer d) {
    if (sock < 0) { log_message("❌ Not connected!"); return; }
    unsigned char packet[5] = {0xBB,0x01,0x02,0x25,0xCC};
    unsigned char buffer[1024] = {0};
    send(sock, packet, sizeof(packet), 0);
    log_message("➡ Sent Packet 25");
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        char logbuf[512] = "⬅ Reply 25: ";
        for (int i=0;i<valread;i++){ char tmp[8]; snprintf(tmp,8,"%02X ",buffer[i]); strcat(logbuf,tmp);}
        log_message(logbuf);
    }
}

// === Send all packets ===
void send_all(GtkWidget *w, gpointer d) {
    log_message("🚀 Sending all packets...");
    send_packet21(NULL,NULL); sleep(1);
    send_packet22(NULL,NULL); sleep(1);
    send_packet23(NULL,NULL); sleep(1);
    send_packet24(NULL,NULL); sleep(1);
    send_packet25(NULL,NULL);
    log_message("✅ Finished sending all packets.");
}

// === Connect to server ===
void connect_to_server(GtkWidget *w, gpointer d) {
    const char *ip = gtk_entry_get_text(GTK_ENTRY(ip_entry));

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        log_message("❌ Socket creation failed!");
        return;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        log_message("❌ Invalid IP address.");
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        log_message("❌ Connection failed!");
        close(sock);
        sock = -1;
        return;
    }

    log_message("✅ Connected to server.");
    set_packet_buttons_sensitive(TRUE);
}

// === Disconnect from server ===
void disconnect_from_server(GtkWidget *w, gpointer d) {
    if (sock >= 0) {
        close(sock);
        sock = -1;
        log_message("🔌 Disconnected from server.");
    } else {
        log_message("⚠️ No active connection to disconnect.");
    }
    set_packet_buttons_sensitive(FALSE);
}

// === Load CSS ===
void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
    g_object_unref(provider);
}

// === Main GUI ===
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    load_css();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "TCP/IP Client GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // IP + Connect/Disconnect
    GtkWidget *conn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    ip_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(ip_entry), "Enter server IP (e.g. 127.0.0.1)");
    // GtkWidget *connect_btn = gtk_button_new_with_label("Connect");
    // GtkWidget *disconnect_btn = gtk_button_new_with_label("Disconnect");
    GtkWidget *connect_btn = gtk_button_new_with_label("Connect");
    gtk_widget_set_name(connect_btn, "connect_btn");

    GtkWidget *disconnect_btn = gtk_button_new_with_label("Disconnect");
    gtk_widget_set_name(disconnect_btn, "disconnect_btn");



    g_signal_connect(connect_btn, "clicked", G_CALLBACK(connect_to_server), NULL);
    g_signal_connect(disconnect_btn, "clicked", G_CALLBACK(disconnect_from_server), NULL);

    gtk_box_pack_start(GTK_BOX(conn_box), ip_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(conn_box), connect_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(conn_box), disconnect_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), conn_box, FALSE, FALSE, 0);

    // Packet buttons
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    packet_buttons[0] = gtk_button_new_with_label("Packet 21");
    packet_buttons[1] = gtk_button_new_with_label("Packet 22");
    packet_buttons[2] = gtk_button_new_with_label("Packet 23");
    packet_buttons[3] = gtk_button_new_with_label("Packet 24");
    packet_buttons[4] = gtk_button_new_with_label("Packet 25");
    packet_buttons[5] = gtk_button_new_with_label("Send All");

    g_signal_connect(packet_buttons[0], "clicked", G_CALLBACK(send_packet21), NULL);
    g_signal_connect(packet_buttons[1], "clicked", G_CALLBACK(send_packet22), NULL);
    g_signal_connect(packet_buttons[2], "clicked", G_CALLBACK(send_packet23), NULL);
    g_signal_connect(packet_buttons[3], "clicked", G_CALLBACK(send_packet24), NULL);
    g_signal_connect(packet_buttons[4], "clicked", G_CALLBACK(send_packet25), NULL);
    g_signal_connect(packet_buttons[5], "clicked", G_CALLBACK(send_all), NULL);

    for (int i = 0; i < 6; i++)
        gtk_box_pack_start(GTK_BOX(btn_box), packet_buttons[i], TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(main_box), btn_box, FALSE, FALSE, 0);

    // Log area
    log_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(log_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(log_view), GTK_WRAP_WORD_CHAR);
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), log_view);
    gtk_box_pack_start(GTK_BOX(main_box), scroll, TRUE, TRUE, 0);

    // Disable buttons initially
    set_packet_buttons_sensitive(FALSE);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
