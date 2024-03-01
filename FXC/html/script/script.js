function buttonFilter() {
    let buttonElements = document.getElementsByTagName('button');
    let button;
    let name;

    for (let i = 0; i < buttonElements.length; i++) {
        if (buttonElements[i].type === 'submit' || buttonElements[i].type === 'button'|| buttonElements[i].type === 'reset') {
            if ((buttonElements[i].name !== document.forms[0].buttonHit.value))
                buttonElements[i].disabled = 1;
            else {
                name = buttonElements[i].name;
                buttonElements[i].name = 'NoUse';
                buttonElements[i].disabled = 1;
            }
        }
    }

    button = document.getElementsByName('buttonValue');
    button[0].name = name;
    button = document.getElementsByName('buttonHit');
    button[0].disabled = 1;

}

function buttonClick(btn,value) {
    let button;
    
    button = document.getElementsByName('buttonHit');
    button[0].value = btn.name;

    button = document.getElementsByName('buttonValue');
    button[0].value = value;

    return true;
}

function clickButton(message) {
    alert(message);
}

function mainOnload() {
    
}

function changeCursorPointer() {
    document.body.style.cursor = 'pointer';
}

function changeCursorDefault() {
    document.body.style.cursor = 'default';
}

/**************************************************************************/
function getElementsByName_iefix(tag, name) {
     const elem = document.getElementsByTagName(tag);
     let arr = new Array();
     let i;
     let iarr;
     for (i = 0,iarr = 0; i < elem.length; i++) {
          att = elem[i].getAttribute("name");
          if(att === name) {
               arr[iarr] = elem[i];
               iarr++;
          }
     }

     return arr;
}  

function grayout_button(ButtonName) {
    let selectedButton = $('#' + ButtonName);
    selectedButton[0].disabled = true;
}

function ungrayout_button(ButtonName) {
    let selectedButton = $('#' + ButtonName);
    selectedButton[0].disabled = false;
}

function changePwdVisibleStatus(id) {
    if (document.getElementById(id).type === "password") {
        document.getElementById(id).type = "text";
        document.getElementById(id+"Slash").style.display = "none";
    } else {
        document.getElementById(id).type = "password";
        document.getElementById(id+"Slash").style.display = "";
    }
}

function bind_mui_textfield() {
    $("input").focus(function() {
        if ($(this).hasClass('error'))
            $(this).removeClass('error');
    });
}

function clear_mui_textfield_error(obj) {
    obj.removeClass('error');
}

function set_mui_textfield_error(obj) {
    if (!obj.hasClass('error'))
        obj.addClass('error');
}

class Dialog {
    constructor(dialog_html, bind_view) {
        this.html = dialog_html;
        this.bind_view = bind_view;
        this.is_show = false;
        this.cancel = false;
    }

    setCanceledOnTouchOutside(cancel) {
        this.cancel = cancel;
        return this;
    }

    isShow() {
        return this.is_show;
    }

    show() {
        this.is_show = true;
        $(this.bind_view).append(this.html);
    }
}

class CardDialog extends Dialog {
    constructor(dialog_html) {
        super(`<div class="dialog-container dialog-center">
                <div class="dialog-popup">${dialog_html}</div></div>`, 'body');
    }

    show() {
        super.show();
        setTimeout(function() {
            $(".dialog-popup").addClass("visible");
            $(".dialog-container").addClass("visible");
        }, 100);

        $(".dialog-container").live('click', (event) => {
            if (this.cancel && $(event.target).closest('.dialog-popup').length === 0) {
                this.distory();
            }
        });
    }

    distory() {
        if (this.is_show) {
            $(".dialog-popup").removeClass("visible");
            $(".dialog-container").removeClass("visible");
            setTimeout(function() {
                $(".dialog-container").remove();
            }, 200);
        }
    }
}

class Loading extends Dialog {
    constructor() {
        super(`<div class="dialog-container dialog-center">
            <div class="holder" id="load-frame">
            <div class="preloader"><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div></div>
            </div></div>`, 'body');
    }

    show() {
        super.show();
        setTimeout(function() {
            $(".dialog-container").addClass("visible");
        }, 100);

        return this;
    }

    distory() {
        if (this.is_show) {
            $("#load-frame").css("display", "none");
            $(".dialog-container").removeClass("visible");
            setTimeout(function() {
                $(".dialog-container").remove();
            }, 200);
        }
    }
}

class Progress extends Dialog {
    constructor(msg) {
        super(`<div class="progress-frame">
            <div class="progress-bar"></div>
            <h1 class="count">0%</h1>
            <div class="info">${msg}</div>
            </div>`, '#wrapper');
    }

    show() {
        super.show();
        $(".progress-frame").addClass("visible");
    }

    update(i) {
        if (this.is_show) {
            if (i <= 100) {
                document.querySelector('.progress-bar').style.width = i + '%';
                document.querySelector('.count').innerHTML = Math.round(i) + '%';
            } else {
                document.querySelector('.progress-bar').className += " done";
                document.querySelector('.count').innerHTML = '100%';
                document.querySelector('.count').className += " done";
                document.querySelector('.info').className += " done";
            }
        }
    }

    distory() {
        if (this.is_show) {
            $(".progress-frame").removeClass("visible");
            setTimeout(function() {
                $(".progress-frame").remove();
            }, 200);
        }
    }
}

class Logout extends Dialog {
    constructor() {
        super(`<div class="progress-frame">
            <div class="progress-bar done"></div>
            <h1 class="count done" style="width: 100%"><%getstr("logout_info");%></h1>
            <div class="info done"><%getstr("logout_goodbye");%></div>
            </div>`, '#wrapper');
    }

    show() {
        super.show();
        $('.sidebar').remove();
        $('.main-panel').remove();
        $(".progress-frame").addClass("visible");
        $('script').remove();
    }
}

function bind_view(obj) {
    $('[show]').each(function() {
        if (obj.hasOwnProperty($(this).attr('show'))) {
            if (obj[$(this).attr('show')])
                $(this).removeAttr('show');
            else
                $(this).remove();
        } else {
            $(this).removeAttr('show');
        }
    });
}

function load_page(page) {
    $('#page').css("display","none");
    $('#roller-frame').css("display","block");
    $('#page').attr("src", page);
    $('#page').load(function() {
        $('#page').css("display","");
        $('#roller-frame').css("display","none");
    });
}

function trigger_open() {
    $("#wrapper").addClass("nav_open");

    setTimeout(function() {
        $("#toggler").addClass("toggled");
    }, 200);
}

function trigger_close() {
    $("#wrapper").removeClass("nav_open");

    setTimeout(function() {
        $("#toggler").removeClass("toggled");
    }, 200);
}

function trigger_logout() {
    $.ajax({
        url: "ajax/logout",
        dataType: "json",
        type: "POST",
        success: function(data) {
            if (data !== null) {
                new Logout().show();
            }
        }
    });
}

function trigger_reboot() {
    $.ajax({
        url: "ajax/reboot",
        dataType: "json",
        type: "POST",
        success: function(data) {
            if (data !== null) {
                $('.sidebar').remove();
                $('.main-panel').remove();
                let logout = new Progress("Rebooting...");
                logout.show();
                reboot_loading(logout, 0);
            }
        }
    });
}

function reboot_loading(target, progress) {
    if (progress <= 100) {
        target.update(progress++);
        setTimeout(function() {
            reboot_loading(target, progress);
        }, 1200);
    } else {
        target.update(progress);
        top.location.href = "start.htm";
    }
}

function nav_profile_trigger() {
    if ($("#profile_menu").hasClass("show"))
        $("#profile_menu").removeClass("show");
    else
        $("#profile_menu").addClass("show");
}

function nav_enable() {
    $(".nav-item").removeClass("nav-disabled");
}

function ap_mode_disabled() {
    $(".nav-item").removeClass("nav-disabled");
    $(".nav-ap").each(function() {                
        $(this).addClass("nav-disabled");
    });
}

function sta_mode_disabled() {
    $(".nav-item").removeClass("nav-disabled");
    $(".nav-sta").each(function() {                
        $(this).addClass("nav-disabled");
    });
}

function trigger_dev_control() {
    $("#nav-dev-controll").click();
}

function trigger_dev_name() {
    if ($("#nav-setup").children("a").attr("aria-expanded") == "false")
        $("#nav-setup").click();

    $("#nav-dev-name").click();
}

function trigger_wireless() {
    if ($("#nav-setup").children("a").attr("aria-expanded") == "false")
        $("#nav-setup").click();
    
    $("#nav-wireless").click();
}

let progress = null;
function show_progress(msg) {
    if (progress === null) {
        progress = new Progress(msg);
        progress.show();
    }
}

function update_progress(i) {
    if (progress !== null) {
        progress.update(i)
    }
}

function hide_progress(i) {
    if (progress !== null) {
        progress.distory(i)
        progress = null
    }
}

let loading = null;
function show_loading() {
    if (loading === null) {
        loading = new Loading();
        loading.show();
    }
}

function hide_loading() {
    if (loading !== null) {
        loading.distory();
        loading = null;
    }
}
